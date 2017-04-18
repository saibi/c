/*!
  \file inverter.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Tue May 24 10:09:42 KST 2011

*/
#include <inverter.h>

// 20110905 110V booster type inverter test items
// - comm waiting time
// - default voltage value (110, 220, 110 booster)
// - trip value 

// debugging macros
#define DBG(x) 
#define DBG_UART(x) 
#define DUMP_STAT


#if defined(INV_HPE7000)
#include <hex_motor_common.h>
#define PR SSL_PRINTF
#define UART_INIT uart_init
#define IS_STOP_PRESSED() CHECK_STOP_SIGNAL()

#elif defined(INV_CPE4000)
#include <cpe_motor_common.h>
#define PR PRINTF
#define SAIBI_ABS(x) ( (x) < 0 ? -(x) : (x) )
#define UART_INIT Uart_Init

#define IS_STOP_PRESSED() IS_STOP_KEY_PUSHED()

#elif defined(INV_NEX)
#include <nex_inv_header.h>

#define PR SSL_PRINTF
#define UART_INIT uart_init
#define IS_STOP_PRESSED() (0)

#define ERR_ANS_STOP 0

#else
#error Please define Product type (INV_ XXX) in the Makefile
#endif


#define UART_INVERTER 1
#define MAX_INV_ISR_LEN (MAX_INV_REPLY_LEN*20 + 1)
#define INVERTER_REPLY_TIMEOUT 15 // wait 1.5 second

#define NORMAL_DCV_220 330 
#define NORMAL_DCV_110 160
#define MAX_DCV_110 220 

#define OVER_VOLT_P 130
#define START_STOP_RETRY_FREQ_P 110
#define MIN_START_FREQ_P 60 // 80 ,  80~120 blocked too long
#define MAX_START_FREQ_P 140 // 120
#define LOW_CUR 2
#define MAX_ZERO_CURRENT 10
#define MAX_LOW_FREQ 5
#define LOW_FREQ_P 30
#define LOW_VOLT_P 50

#define INV_FLAG_TX_ISR 0x01
#define INV_FLAG_ABNORMAL_VAL 0x02
#define INV_FLAG_DISABLE 0x04 // do not use inverter error check 
#define INV_FLAG_ENABLE_RCV_CHECK 0x08 // enable return packet check 
#define CRC_RETRY_COUNT 3

// inverter status string for HPE-7000
char inverter_status_str[128];

INV_META inv_meta = {
	0, // type
	0, // stop tick 
	INV_FLAG_DISABLE, // flag
	{0, }, // msg
	20000, // HI
	13000, // LO
	0,

	35, // timeout seconds
	330, // normal dcv (220v) 
	330, // start dcv (220v)

#if defined(INV_HPE7000)
	15, // stop-start interval 
#elif defined(INV_CPE4000) 
	4,
#elif defined(INV_NEX) 
	10, // 8 -> 10
#else
	10,
#endif 
};

typedef struct _inv_info_rec {
	int trip;
	int freq;
	int cur;
	int dcv;
} INV_INFO;

// inverter packet list
static char inv_packet_list[MAX_INV_CMD_IDX][MAX_INV_CMD_LEN] = {
	// reply command
	{ 0x01, 0x03, 0x12,	0x05,	0x00, 0x01,		0x91, 0x73 }, // dcv
	{ 0x01, 0x03, 0x12,	0x01,	0x00, 0x01,		0xd0, 0xb2 }, // freq
	{ 0x01, 0x03, 0x12,	0x03,	0x00, 0x01,		0x71, 0x72 }, // current
	{ 0x01, 0x03, 0x12,	0x0d,	0x00, 0x01,		0x10, 0xb1 }, // trip

	// command
	{ 0x01, 0x13, 0x02, 0x10, 	0x00, 0x00,		0x84, 0x74 }, // start
	{ 0x01, 0x13, 0x01, 0x10, 	0x00, 0x00,		0x84, 0x30 }, // stop
	{ 0x01, 0x13, 0x06, 0x10, 	0x00, 0x00,		0x85, 0x44 }, // reset 
};





// for inverter usrt isr
static char isr_buf[MAX_INV_ISR_LEN];
static volatile int isr_pos;

/// return inverter type
/// \return type
int get_inverter_meta_type(void)
{
	return inv_meta.type;
}

/// return inverter meta check status
/// \return 0 - disabled, 1- enabled 
int get_inverter_meta_stat(void)
{
	return (inv_meta.flag & INV_FLAG_DISABLE ) ? 0 : 1;
}


/// inverter uart isr 
static void __irq inverter_isr(void)
{
	int ch;

	rI_ISPC = BIT_URXD1;	// Clear pending bits, default value = 0x000000;

	// for FIFO
	while ( ( rUFSTAT1 & 0xf ) > 0 ) {
		ch = rURXH1;
		if ( isr_pos < MAX_INV_ISR_LEN ) {
			isr_buf[isr_pos++] = ch;
		}
	}
}

/// enable inverter uart isr 
static void enable_inverter_isr(void)
{
	pISR_URXD1=(unsigned)inverter_isr;
	rINTMSK &= ~(BIT_GLOBAL | BIT_URXD1);

	memset(isr_buf, 0, sizeof(isr_buf));
	isr_pos = 0;
	DBG(PR("DEBUG enable inverter isr\n"));
}

/// disable inverter uart isr
static void disable_inverter_isr(void)
{
	rINTMSK |= BIT_URXD1;
	DBG(PR("DEBUG disable inverter isr\n"));
}

/// inverter uart init (enable TX/RX FIFO)
static void inverter_uart_init(void)
{
	int i;

	rUFCON1=0x97; // tx fifo 8 bytes, rx fifo 8bytes, tx fifo reset, rx fifo reset, fifo enable
	rUMCON1=0x0;
	rULCON1=0x3;   //Normal,No parity,1 stop,8 bit
	rUCON1=0x245;
	rUBRDIV1=( (int)(MCLK/16./2400+ 0.5) -1 );
	
	for(i=0;i<100;i++)
		;
}

/// write to inverter (FIFO)
static void inverter_uart_write(char *data)
{
	int sent = 0;
	int cnt = 0;

	if ( !(inv_meta.flag & INV_FLAG_TX_ISR) ) { 
		PR("please check the inverter uart TX/RX isr.\n");
		return;
	}

	while ( sent < MAX_INV_CMD_LEN ) {
		while (rUFSTAT1 & 0x200)
			;

		cnt = 16 - ((rUFSTAT1 & 0xf0) >> 4);
		while ( cnt > 0 && (sent < MAX_INV_CMD_LEN) ) {
			rUTXH1 = data[sent++];
			cnt --;
		}
	}
}

/// read remained data from fifo
static void inverter_read_fifo(void)
{
	int fifo_cnt = rUFSTAT1 & 0xf;

	while(fifo_cnt--) {
		isr_buf[isr_pos++] = rURXH1;
	}
}

/// Start inverter uart TX/RX ISR 
static void inv_trx_isr_start(void)
{
	if ( inv_meta.flag & INV_FLAG_TX_ISR ) { 
		return;
	}
	enable_inverter_isr();
	inverter_uart_init(); // TX/RX fifo

	inv_meta.flag |= INV_FLAG_TX_ISR;
}

/// Stop inverter uart TX/RX ISR 
static void inv_trx_isr_stop(void)
{
	if ( !(inv_meta.flag & INV_FLAG_TX_ISR) ) { 
		return;
	}
	inverter_read_fifo();
	disable_inverter_isr();
	UART_INIT(UART_INVERTER, 2400); // reset uart - disable TX/RX Fifo

	inv_meta.flag &= (~INV_FLAG_TX_ISR);
}


/// set inverter frequency
/// \param hi
/// \param lo
void set_inverter_frequency(int hi, int lo)
{
	inv_meta.freq_hi = hi;
	inv_meta.freq_lo = lo;
}

/// enable/disable inverter check
/// \param stat 1-enable, 0-disable
void enable_inverter_check(int stat)
{
	if ( stat ) {
		inv_meta.flag &= (~INV_FLAG_DISABLE);
		PR("Enable Inverter Checking\n");
	} else {
		inv_meta.flag |= INV_FLAG_DISABLE;
		PR("Disable Inverter Checking\n");
	}
}

/// enable/disable inverter return packet check 
/// \param stat 1-enable, 0-disable
void enable_inverter_rcv_check(int stat)
{
	if ( stat ) {
		inv_meta.flag |= INV_FLAG_ENABLE_RCV_CHECK;
		PR("Enable inverter return packet check\n");
	} else {
		inv_meta.flag &= (~INV_FLAG_ENABLE_RCV_CHECK);
		PR("Disable inverter return packet check\n");
	}
}



/// Calc CRC
static unsigned short AddData(unsigned short crc, unsigned short data)
{
	unsigned short out,i;
	out = crc^data;
	for(i=0;i<8;i++){
		if(out&1) out= (out>>1)^0xa001;
		else
			out= out>>1;
	}
	return out;
}

/// Calc CRC
static unsigned short GetCRC(unsigned char * data, int len)
{
	unsigned short wSeed,i;
	wSeed = 0xffff;
	for(i=0;i<len;i++){
		wSeed = AddData(wSeed,*data++);
	}
	return ((wSeed<<8)|(wSeed>>8));
}

/// fill crc value
/// \param msg (in/out) msg[6], msg[7]
static void fill_crc(char *msg)
{
	unsigned short crc;

	crc = GetCRC((unsigned char *)msg, 6);
	msg[6] = ( crc >> 8 ) & 0xff;
	msg[7] =  crc & 0xff;
}

/// check crc value 
/// \param msg
/// \param len  7 or 8
/// \param dbg_msg 1-print debug message
/// \return 0 ok
/// \return -1 crc error
static int check_crc(char *msg, int len, int dbg_msg)
{
	unsigned short crc;
	char calc[2];

	crc = GetCRC((unsigned char *)msg, len-2);
	calc[0] = (crc >> 8 ) & 0xff;
	calc[1] = crc & 0xff;

	if ( calc[0] != msg[len-2] || calc[1] != msg[len-1] ) {
		if ( dbg_msg ) {
			PR("Inverter packet CRC mismatch : rcv %x %x, calc %x %x\n", calc[0], calc[1], msg[len-2], msg[len-1]);
		}
		return -1;
	}
	return 0;
}

#if 0
/// DEBUG : CRC test
static void test_crc(void)
{
	unsigned char test[8] = { 0x01, 0x03, 0x12,	0x05,	0x00, 0x01, 0, 0 };
	unsigned char test2[8]={ 0x01, 0x03, 0x12,	0x01,	0x00, 0x01, 0xd0, 0xb2 };
	unsigned char test3[8] ={ 0x01, 0x13, 0x02, 0x10, 	0x00, 0x00,		0x00, 0x00 };
	unsigned char test4[8] ={ 0x01, 0x13, 0x01, 0x10, 	0x00, 0x00,		0x00, 0x00 };
	unsigned char test5[8] = { 0x01, 0x13, 0x06, 0x10, 	0x00, 0x00,		0x00, 0x00 };
	unsigned short ret;

	ret = GetCRC(test, 6);
	PR("crc = %d, %x, 0x%x 0x%x\n", ret, ret, ( ret >> 8) & 0xff, ret & 0xff );
	ret = GetCRC(test2, 6);
	PR("crc = %d, %x, 0x%x 0x%x\n", ret, ret, ( ret >> 8) & 0xff, ret & 0xff );
	ret = GetCRC(test3, 6);
	PR("crc = %d, %x, 0x%x 0x%x\n", ret, ret, ( ret >> 8) & 0xff, ret & 0xff );
	ret = GetCRC(test4, 6);
	PR("crc = %d, %x, 0x%x 0x%x\n", ret, ret, ( ret >> 8) & 0xff, ret & 0xff );
	ret = GetCRC(test5, 6);
	PR("crc = %d, %x, 0x%x 0x%x\n", ret, ret, ( ret >> 8) & 0xff, ret & 0xff );
}
#endif 

/// print meta values
void pr_inverter_meta(void)
{
	PR("type = %d\n", inv_meta.type);
	PR("stop_tick = %d\n", inv_meta.stop_tick);
	PR("flag = %d\n", inv_meta.flag);

	PR("freq_hi = %d\n", inv_meta.freq_hi);
	PR("freq_lo = %d\n", inv_meta.freq_lo);
	PR("timeout = %d\n", inv_meta.timeout);
	PR("normal_dcv = %d\n", inv_meta.normal_dcv);
	PR("start_dcv = %d\n", inv_meta.start_dcv);
	PR("start_interval = %d\n", inv_meta.start_interval);
}

/// eat garbage data in the uart
static void clear_inv_uart(void)
{
	int i;
#define CLEAR_CNT 10

	// clear read buffer
	for ( i = 0 ; i < CLEAR_CNT;i++ ) {
		uart_read_byte(UART_INVERTER);
	}
}

/// send message
/// \param msg
/// \return 0 success
/// \return -INV_ERR_TOO_FAST
static int send_inverter(char *msg)
{
	static unsigned int tick_sent = 0;
	unsigned int cur_tick;

	cur_tick = get_rtc_tick();
	if ( tick_sent > cur_tick ) {
		// reset
		tick_sent = 0;
	}

	// to prevent sending packet within 1/4 sec
	if ( (tick_sent + get_rtc_tick_per_second()/4) > cur_tick ) {
		return -INV_ERR_TOO_FAST;
	}
	tick_sent = get_rtc_tick();

	// send 8 bytes
	uart_write_b(UART_INVERTER, msg, MAX_INV_CMD_LEN);
	DBG_UART(PR("DEBUG INV SEND : "));
	DBG_UART(dump_buf(msg, MAX_INV_CMD_LEN, "%02x ", 10));

	return 0;
}

/// send message (DEBUG)
/// \param msg
/// \return 0 success
/// \return -INV_ERR_TOO_FAST
static int send_inverter_debug(char *msg)
{
	static unsigned int tick_sent = 0;
	unsigned int cur_tick;

	cur_tick = get_rtc_tick();
	if ( tick_sent > cur_tick ) {
		// reset
		tick_sent = 0;
	}

	// to prevent sending packet within 1/4 sec
	if ( (tick_sent + get_rtc_tick_per_second()/4) > cur_tick ) {
		return -INV_ERR_TOO_FAST;
	}
	tick_sent = get_rtc_tick();

	// send 8 bytes
	uart_write_b(UART_INVERTER, msg, MAX_INV_CMD_LEN);
	PR("DEBUG INV SEND : ");
	dump_buf(msg, MAX_INV_CMD_LEN, "%02x ", 10);

	return 0;
}

static int (*send_inverter_func)(char *) = send_inverter; 

/// receive inverter packet
/// \param len bytes to read, 7 or 8
/// \param rcv_msg (out) returned packet
/// \return 0 success
/// \return -INV_ERR_REPLY_TIMEOUT
static int recv_inverter(int len, char *rcv_msg)
{
	int ret = -1;
	int i = 0;
	unsigned int end_tick;

	end_tick = get_rtc_tick() + (INVERTER_REPLY_TIMEOUT * get_rtc_tick_per_second() ) / 10;
	while ( get_rtc_tick() < end_tick) {
		ret = uart_read_byte(UART_INVERTER);
		if (ret >= 0) {
			rcv_msg[i++] = ret;
			if ( i >= len ) {
				break;
			}
		}
	}
	if ( ret < 0 ) {
		return -INV_ERR_REPLY_TIMEOUT;
	}
	DBG_UART(PR("DEBUG INV RECV : "));
	DBG_UART(dump_buf(rcv_msg, len, "%02x ", 10));
	if ( check_crc(rcv_msg, len, 0) < 0 )  {
		return -INV_ERR_CRC;
	}
	return 0;
}

/// receive inverter packet (DEBUG)
/// \param len bytes to read, 7 or 8
/// \param rcv_msg (out) returned packet
/// \return 0 success
/// \return -INV_ERR_REPLY_TIMEOUT
static int recv_inverter_debug(int len, char *rcv_msg)
{
	int ret = -1;
	int i = 0;
	unsigned int end_tick;

	end_tick = get_rtc_tick() + (INVERTER_REPLY_TIMEOUT * get_rtc_tick_per_second() )/ 10;
	while ( get_rtc_tick() < end_tick) {
		ret = uart_read_byte(UART_INVERTER);
		if (ret >= 0) {
			rcv_msg[i++] = ret;
			if ( i >= len ) {
				break;
			}
		}
	}
	if ( ret < 0 ) {
		return -INV_ERR_REPLY_TIMEOUT;
	}
	PR("DEBUG INV RECV : ");
	dump_buf(rcv_msg, len, "%02x ", 10);
	if ( check_crc(rcv_msg, len, 1) < 0 )  {
		return -INV_ERR_CRC;
	}
	return 0;
}

static int (*recv_inverter_func)(int, char *) = recv_inverter; 

/// send wheel start/stop, reset command
/// \param msg
/// \return trip_status
static int send_cmd(char *msg)
{
	int ret = 0;

	clear_inv_uart();

	if ( (ret = send_inverter_func(msg)) < 0 ) {
		return ret;
	}

	if ( (inv_meta.flag & INV_FLAG_DISABLE) && !(inv_meta.flag & INV_FLAG_ENABLE_RCV_CHECK) ) {
		int i;
		// clear received data
		for ( i = 0 ; i < 16 ; i++ ) {
			uart_read_byte(UART_INVERTER);
		}
	} else {
		memset(inv_meta.ret_msg, 0, sizeof(inv_meta.ret_msg));
		if ( (ret = recv_inverter_func(MAX_INV_CMD_LEN, inv_meta.ret_msg)) < 0 ) {
			return ret;
		}
		ret = inv_meta.ret_msg[5];
	}
	return ret;
}

/// send cmd (blocking version)
static int send_cmd_b(char *msg)
{
	int ret;

	while( (ret = send_cmd(msg)) == -INV_ERR_TOO_FAST ) {
		Delay(100);
	}
	return ret;
}

/// request inverter info 
/// \param msg
/// \return info 
/// \return -INV_ERR_REPLY_TIMEOUT
static int req_inverter(char *msg)
{
	int ret;

	clear_inv_uart();

	if ( (ret = send_inverter_func(msg)) < 0 ) {
		return ret;
	}

	memset(inv_meta.ret_msg, 0, sizeof(inv_meta.ret_msg));

	if ( (ret = recv_inverter_func(MAX_INV_REPLY_LEN, inv_meta.ret_msg)) < 0 ) {
		return ret;
	}

	ret = inv_meta.ret_msg[3];
	ret <<= 8;
	ret += inv_meta.ret_msg[4];
	return ret;
}

/// request inverter info (blocking version)
static int req_inverter_b(char *msg)
{
	int ret;

	while( (ret = req_inverter(msg)) == -INV_ERR_TOO_FAST ) {
		Delay(100);
	}
	return ret;
}

/// get inverter status
/// \param type INV_REQ_ xxx
/// \return status_value
/// \return -INV_ERR_REPLY_TIMEOUT
int get_inverter_status(int type)
{
	int ret;
	int crc_retry = 0;

	while (crc_retry < CRC_RETRY_COUNT ) {
		ret = req_inverter_b( inv_packet_list[type]);
		if ( ret == -INV_ERR_CRC ) {
			crc_retry++;
		} else {
			break;
		}
	}
	return ret;
}

/// get inverter frequency
int get_inverter_frequency(void)
{
	return get_inverter_status(INV_REQ_FREQ);
}

/// wheel stop
/// \return trip_status (meaningless)
/// \return -INV_ERR_REPLY_TIMEOUT
int inv_stop(void)
{
	if ( inv_meta.type == INV_TYPE_ERR ) {
		inv_init();
	}

	inv_trx_isr_stop();

	if ( get_inverter_frequency() > 0 ) {
		inv_meta.stop_tick = get_rtc_tick();
	}
	return send_cmd_b(inv_packet_list[INV_CMD_STOP]);
}

/// wheel reset 
/// \return trip_status (meaningless)
/// \return -INV_ERR_REPLY_TIMEOUT
int inv_reset(void)
{
	if ( inv_meta.type == INV_TYPE_ERR ) {
		inv_init();
	}
	inv_trx_isr_stop();

	if ( get_inverter_frequency() > 0 ) {
		inv_meta.stop_tick = get_rtc_tick();
	}
	return send_cmd_b(inv_packet_list[INV_CMD_RESET]);
}

/// wheel run
/// \return trip_status (meaningless)
/// \return -INV_ERR_REPLY_TIMEOUT
int inv_run(int freq)
{
	if ( inv_meta.type == INV_TYPE_ERR ) {
		inv_init();
	}
	inv_trx_isr_stop();

	inv_packet_list[INV_CMD_START][4] = (freq & 0xff00)>>8;
	inv_packet_list[INV_CMD_START][5] = (freq & 0x00ff);
	inv_meta.req_freq = freq;
	fill_crc(inv_packet_list[INV_CMD_START]);

	return send_cmd_b(inv_packet_list[INV_CMD_START]);
}

/// print status
static void pr_stat(INV_INFO *p)
{
	PR("T%d, F%d, C%d, V%d\n", p->trip, p->freq, p->cur, p->dcv);
}

/// wheel init (setup normal dcv)
/// \return 0 ok
/// \return nagative_value error
int inv_init(void)
{
	int sum, i, ret;
#define LOOP 3 

	inv_trx_isr_stop();

	sum = 0;
	for ( i = 0 ; i < LOOP ; i ++ ) {
		ret = get_inverter_status(INV_REQ_DCV);
		if ( ret < 0 ) {
			inv_meta.type = INV_TYPE_ERR;
			inv_meta.normal_dcv = 0;
			PR("Abnormal Inverter\n");
			return ret;
		}
		sum += ret;
	}
	ret = sum / LOOP;
	PR("Inverter DCV = %d\n", ret);
	inv_meta.start_dcv = ret;

	if ( ret < MAX_DCV_110 ) {
		inv_meta.type = INV_TYPE_110;
		inv_meta.normal_dcv = NORMAL_DCV_110;
		PR("110v\n");
	} else { 
		inv_meta.type = INV_TYPE_220;
		inv_meta.normal_dcv = NORMAL_DCV_220;
		PR("220v\n");
	}

	if ( inv_meta.flag & INV_FLAG_DISABLE ) {
		PR("Inverter check routine disabled.\n");
	}

	inv_reset(); // 20110915 to reset 110V booster type inverter TRIP code 1
	return 0;
}

/// INV_INFO to string
/// \param p
static void make_inverter_status_str(INV_INFO *p)
{
	sprintf(inverter_status_str, "INVERTER T%d, %d %d %d", p->trip, p->freq, p->cur, p->dcv);
}

/// wheel start
/// \param frequency
/// \return 0 success
/// \return -INV_ERR_RETPLY_TIMEOUT inverter down
/// \return -INV_ERR_TIMEOUT 
int inv_start_ex(int freq)
{
	INV_INFO stat;
	unsigned int tick_check, start_tick;
	int ret = 0;
	int retry = 0;
	int err = 0;
	int prev_err = 0;
	int start_dcv = 0;

	inv_trx_isr_stop();

	DBG(PR("DEBUG %s(%d) : start tick = %d\n", __FILE__, __LINE__, get_rtc_tick()));

	if ( inv_meta.stop_tick ) { // 20110906 wait start-stop interval 110/220 both case
		PR("Wait [STOP]-[START] interval.\n");
		while ( (inv_meta.stop_tick + inv_meta.start_interval * get_rtc_tick_per_second()) > get_rtc_tick()) 
			;

		PR("Start\n");
	}

	// release TRIP status first
	if ( get_inverter_status(INV_REQ_TRIP) != 0 ) {
		inv_reset();
	}

	ret = inv_run(freq);
	DBG(PR("DEBUG inv_run = %d\n", ret));
	if ( ret == -INV_ERR_REPLY_TIMEOUT ) {
		return ret;
	}

	if ( inv_meta.flag & INV_FLAG_DISABLE ) {
		return 0;
	}

	if ( inv_meta.type == INV_TYPE_110B ) {
		start_dcv = NORMAL_DCV_220;
	} else {
		start_dcv = inv_meta.start_dcv;
	}

	err = 0;
	start_tick = get_rtc_tick();
	tick_check = start_tick + get_rtc_tick_per_second() * inv_meta.timeout;
	while (1) {
		if ( IS_STOP_PRESSED() ) {
			PR("[STOP] key pressed. Cancel inv_start_ex.\n");
			inv_reset();
			return 0;
		}

		stat.freq = get_inverter_status(INV_REQ_FREQ);
		stat.trip = get_inverter_status(INV_REQ_TRIP);
		stat.cur = get_inverter_status(INV_REQ_CUR);
		stat.dcv = get_inverter_status(INV_REQ_DCV);
#ifdef DUMP_STAT
		pr_stat(&stat);
#endif 

		if ( (stat.freq == -INV_ERR_REPLY_TIMEOUT) || 
			(stat.trip == -INV_ERR_REPLY_TIMEOUT) ||
			(stat.cur == -INV_ERR_REPLY_TIMEOUT) ||
			(stat.dcv == -INV_ERR_REPLY_TIMEOUT) ) {
			// inverter down
			ret = -INV_ERR_REPLY_TIMEOUT;
			break;
		}

		if ( (stat.freq == -INV_ERR_CRC ) || 
			(stat.trip == -INV_ERR_CRC ) ||
			(stat.cur == -INV_ERR_CRC ) ||
			(stat.dcv == -INV_ERR_CRC ) ) {
			// inverter packet crc error
			ret = -INV_ERR_CRC;
			break;
		}

		if ( (stat.trip == 0) && (stat.freq >= (freq * MIN_START_FREQ_P / 100)) && (stat.freq <= (freq * MAX_START_FREQ_P / 100)) && (stat.cur > 0 ) ) {
			ret = 0;

			// check 110V booster type 
			if ( inv_meta.type == INV_TYPE_110 ) {
				if ( stat.dcv > MAX_DCV_110 ) {
					inv_meta.type = INV_TYPE_110B;
					inv_meta.normal_dcv = NORMAL_DCV_220;
					PR("110V Booster type inverter.\n");
				}
			}
			break;
		}

		if ( err == 0 ) {
			// check trip status
			if ( stat.trip >= INV_ERR_OVER_CURRENT && stat.trip <= INV_ERR_LOW_VOLTAGE ) {
				err = stat.trip;
				PR("Inverter TRIP = %d\n", stat.trip);
			} else if ( stat.trip != 0 ) { 
				PR("Inverter unknown trip = %d\n", stat.trip);
				ret = -INV_ERR_UNKNOWN;
				break;
			} else if ( get_rtc_tick() > (start_tick + get_rtc_tick_per_second() * 2 ) ) {
				if ( stat.dcv <= inv_meta.normal_dcv * LOW_VOLT_P/ 100 ) {
					err = INV_ERR_LOW_VOLTAGE;
					PR("Inverter TRIP = 0, LOW VOLT\n");
				}
			}
		} else {
			// 20110707 rewrite recover code

			// check dcv 
			if ( stat.dcv <= (start_dcv * START_STOP_RETRY_FREQ_P / 100) ) {
				if ( retry < 2 ) { 
					retry++;
					PR("Inverter err %d, reset & retry %d\n", err, retry+1);
					ret = inv_reset();
					DBG(PR("DEBUG inv_reset = %d\n", ret));
					ret = inv_run(freq);
					DBG(PR("DEBUG inv_run = %d\n", ret));

					// reset error flag 
					prev_err = err;
					err = 0;
				} else {
					ret = -err;
					break;
				}
			}
		}

		if ( get_rtc_tick() > tick_check ) {
			if ( err != 0 ) {
				ret = -err;
			} else if ( prev_err != 0 ) { 
				ret = -prev_err;
			} else {
				ret = -INV_ERR_TIMEOUT;
			}
			break;
		}

	}
	DBG(PR("DEBUG %s(%d) : end tick = %d\n", __FILE__, __LINE__, get_rtc_tick()));

	make_inverter_status_str(&stat);
	PR("inv_start_ex = %d\n", ret);
	if ( ret < 0 ) {
		inv_reset();
	}
	return ret;
}

/// wheel start
/// \param seed_flag WHEEL_SPEED_HI, WHEEL_SPEED_LO
/// \return 0 success
/// \return -INV_ERR_RETPLY_TIMEOUT inverter down
/// \return -INV_ERR_TIMEOUT 
int inv_start(int speed_flag)
{
	int freq;

	if ( speed_flag == WHEEL_SPEED_HI ) {
		freq = inv_meta.freq_hi;
	} else {
		freq = inv_meta.freq_lo;
	}
	return inv_start_ex(freq);
}



#define MAX_CMD 4

/// read inverter status values from isr buf
/// \param p (out)
/// \param dump 1-dump isr buffer
static void fetch_isr_msg(INV_INFO *p, int dump)
{
	int i, k;
	int ret[MAX_CMD];

	for (i = 0, k = 3 ; i < MAX_CMD; i++, k += MAX_INV_REPLY_LEN ) {
		if ( dump ) {
			dump_buf(&isr_buf[i*MAX_INV_REPLY_LEN], MAX_INV_REPLY_LEN,  "%02x ", MAX_INV_REPLY_LEN + 1);
		}
		ret[i] = isr_buf[k];
		ret[i] <<= 8;
		ret[i] += isr_buf[k+1];
	}

	p->dcv = ret[0];
	p->freq = ret[1];
	p->cur = ret[2];
	p->trip = ret[3];
}


/// chek trip status
/// \param p
/// \return 0 no error
/// \return 1 error occured, but continued
/// \return negative_value inverter error
static int check_trip(INV_INFO *p)
{
	int answer_code = ERR_ANS_STOP;
	int ret = 0;
	int retry = 0;
	int prev_y_speed = DEFAULT_SPEED_Y;
	static int low_freq_count = 0;
	static int zero_cur_count = 0;
	int y_lift = 0;

#ifdef DUMP_STAT
	pr_stat(p);
#endif

	if ( p->trip == -INV_ERR_CRC || p->freq == -INV_ERR_CRC || p->dcv == -INV_ERR_CRC || p->cur == -INV_ERR_CRC ) {
		PR("Inverter packet CRC error\n");
		return 0;
	}

	if ( p->trip ) {
		// (1) inverter trip
		PR("Inverter Error condition (1)\n");
	} else if ( p->freq < inv_meta.req_freq * LOW_FREQ_P / 100) {
		if ( low_freq_count > MAX_LOW_FREQ ) {
			// (2) inverter normal, but wheel doesn't move because of overload 
			PR("Inverter Error condition (2)\n");
		} else {
			low_freq_count++;
			return 0;
		}
	} else if ( low_freq_count > 0 ) {
		if ( (p->cur < LOW_CUR) && (p->freq == inv_meta.req_freq) ) { 
			if ( inv_meta.flag & INV_FLAG_ABNORMAL_VAL ) {
				// (3) inverter abnormal, wheel doesn't move (freq normal, current abnormal(0~2), voltage normal)
				PR("Inverter Error condition (3)\n");
			} else {
				inv_meta.flag |= INV_FLAG_ABNORMAL_VAL;
				return 0;
			}
		} else {
			return 0;
		}
	} else if ((p->cur == 0 ) && (p->freq == inv_meta.req_freq) ) {
		if ( zero_cur_count > MAX_ZERO_CURRENT ) {
			PR("Inverter Error condition (4)\n");
		} else {
			zero_cur_count++;
			return 0;
		}
	} else {
		// inverter OK

		// clear error flag
		zero_cur_count = 0;
		low_freq_count = 0;
		inv_meta.flag &= (~INV_FLAG_ABNORMAL_VAL);
		return 0;
	}

	// clear error flag
	zero_cur_count = 0;
	low_freq_count = 0;
	inv_meta.flag &= (~INV_FLAG_ABNORMAL_VAL); 

	if ( p->trip >= INV_ERR_OVER_CURRENT && p->trip <= INV_ERR_LOW_VOLTAGE ) {
		ret = -p->trip;
	} else if ( p->dcv < inv_meta.normal_dcv * LOW_VOLT_P/100 ) {
		ret = -INV_ERR_LOW_VOLTAGE;
	} else if ( p->dcv > inv_meta.start_dcv * OVER_VOLT_P/100 ) {
		ret = -INV_ERR_OVER_VOLTAGE;
	// TO-DO : over current
	} else {
		ret = -INV_ERR_OVER_HEAT;
	} 
	PR("Inverter Error %d\n", ret);
	inv_trx_isr_stop();
	pr_stat(p);

#if defined(INV_HPE7000) || defined(INV_NEX)
	make_inverter_status_str(p);
#endif 

	inv_reset();



	////////////////////////////
	// Y lift 

	prev_y_speed = const_speed[MOTOR_Y];
	const_speed[MOTOR_Y] = DEFAULT_SPEED_Y;

	// lift lens
	while ( (PI_PORT & PI_BIT_MAIN_CONTACT) ) {
		move_y_position( motor_abs_pos[MOTOR_Y] - 1000);
		y_lift += 1000;
	}
	move_y_position( motor_abs_pos[MOTOR_Y] - 1000) ;
	y_lift += 1000;
	PR("Lift Y = %d\n", y_lift );

	const_speed[MOTOR_Y] = prev_y_speed; 
	////////////////////////////



	do { 
		retry ++;

		answer_code = ERR_ANS_STOP;
#if defined(INV_HPE7000) 
		send_hmc_error_msg(UART_GUI, inverter_status_str);
		send_hmc_err_req(UART_GUI, inverter_error_to_motor(ret));
		recv_hmc_err_ans(UART_GUI, &answer_code, gui_answer_timeout);
#elif defined(INV_CPE4000)
		enable_uart_handler(UART_GUI);
		send_cpe_motor_err_req(UART_GUI, inverter_error_to_motor(ret));
		recv_cpe_motor_err_ans(UART_GUI, &answer_code, gui_answer_timeout);
		disable_uart_handler(UART_GUI);
#elif defined(INV_NEX)
		PR("send/recv code not implemented.\n");
#endif 
		if ( answer_code == ERR_ANS_STOP ) {
			PR("Inverter Error %d : Cancel\n", ret);
			break;
		}

		ret = inv_start(WHEEL_SPEED_HI);
		if ( ret == 0 ) {
			// back to org pos
			move_y_position( motor_abs_pos[MOTOR_Y] + y_lift) ;
			break;
		}
	} while ( retry < 2 );
	inv_trx_isr_start();

	if ( ret == 0 ) {
		PR("Inverter Error %d : Continue\n", ret);
		return 1;
	}
	PR("Inverter Error %d : Stop\n", ret);
	return ret;
}


/// check inverter status (new isr)
/// \param control_flag 0-start, 1-continue, 2-finish, see INV_CHECK_ xxx
/// \return 0 no error
/// \return 1 error occurred, but continued
/// \return negative_value error
int check_inverter_status(int control_flag)
{
	static int pos = 0, idx = 0;
	static unsigned int last_tick = 0;
	INV_INFO stat;
	int ret = 0;

	if ( inv_meta.flag & INV_FLAG_DISABLE ) {
		return 0;
	}

	if ( control_flag == INV_CHECK_START ) {
		inv_trx_isr_start();
		idx = 0;
		pos = 0;
		last_tick = 0;
	} else if ( control_flag == INV_CHECK_END ) {
		inv_trx_isr_stop();
	} else {
		inv_trx_isr_start();
		if ( idx < MAX_CMD ) {
			if (last_tick == 0 ) {
				//send_inverter_func(inv_packet_list[idx]);
				inverter_uart_write(inv_packet_list[idx]);
				last_tick = get_rtc_tick();
			} else {
				if ( get_rtc_tick() > (last_tick + get_rtc_tick_per_second()/4) ) {
					last_tick = 0;
					idx++;
				}
			}
		} else {
			if ( isr_pos >= (MAX_INV_REPLY_LEN*MAX_CMD) ) {
				fetch_isr_msg(&stat, 0);

				isr_pos = 0;
				idx = 0;
				pos = 0;
				last_tick = 0;

				if ( (ret = check_trip(&stat)) < 0 ) {
					inv_trx_isr_stop();
					return -inverter_error_to_motor(ret);
				} else if ( ret > 0 ) {
					return ret;
				}
			} else {
				if ( last_tick == 0 ) {
					last_tick = get_rtc_tick();
				} else {
					if ( get_rtc_tick() > (last_tick + get_rtc_tick_per_second()/4) ) {
						inverter_read_fifo();
						last_tick = 0;
					}
				}
			}
		}
	}
	return 0;
}

/// wait 1/2 second
static void wait(void)
{
	unsigned int tick;

	tick = get_rtc_tick();
	while ( (tick + get_rtc_tick_per_second()/2) > get_rtc_tick() ) 
		;
}


/// isr tester
void inv_isr_test(int cnt)
{
	unsigned int tick = 0;
	int i = 0;
	INV_INFO stat;

	inv_trx_isr_start();

	if ( cnt == 0 ) { 
		inverter_uart_write(inv_packet_list[INV_REQ_DCV]);
		wait();
		inverter_uart_write(inv_packet_list[INV_REQ_FREQ]);
		wait();
		inverter_uart_write(inv_packet_list[INV_REQ_CUR]);
		wait();
		inverter_uart_write(inv_packet_list[INV_REQ_TRIP]);
		wait();
		cnt = 4;
	} else {
		for (i=0 ; i < cnt ; i++ ) {
			PR("DEBUG Send REQ_DCV\n");
			inverter_uart_write(inv_packet_list[INV_REQ_DCV]);
			wait();
		}
	}

	PR("DEBUG wait, %d\n", isr_pos);
	tick = get_rtc_tick();
	while ( isr_pos < MAX_INV_REPLY_LEN * cnt ) {
		Delay(1);
		if ( uart_read_byte(0) == 'q') {
			PR("DEBUG break\n");
			break;
		}
		if ( (tick + get_rtc_tick_per_second() * 2) < get_rtc_tick() ) {
			break;
		}
	}

	if ( isr_pos <= MAX_INV_REPLY_LEN * cnt ) {
		inverter_read_fifo();
	}
	PR("DEBUG final, %d\n", isr_pos);

	fetch_isr_msg(&stat, 1);
	pr_stat(&stat);

	inv_trx_isr_stop();
}


/// convert error code
int inverter_error_to_motor(int err)
{
	err = SAIBI_ABS(err);

#if defined(INV_HPE7000) || defined(INV_CPE4000)
	if ( err == INV_ERR_OVER_CURRENT ) {
		return ERR_INVERTER_OVER_CURRENT;
	} else if ( err == INV_ERR_OVER_VOLTAGE ) {
		return ERR_INVERTER_OVER_VOLTAGE;
	} else if ( err == INV_ERR_OVER_HEAT ) {
		return ERR_INVERTER_OVER_HEAT;
	} else if ( err == INV_ERR_LOW_VOLTAGE ) {
		return ERR_INVERTER_LOW_VOLTAGE;
	} else if ( err == INV_ERR_UNKNOWN) {
		return ERR_INVERTER_ERROR;
	} else if ( err == INV_ERR_TIMEOUT ) {
		return ERR_INVERTER_LOW_VOLTAGE;
	} else if ( err == INV_ERR_CRC ) {
		return ERR_INVERTER_CRC;
	} else {
		return ERR_INVERTER_TIMEOUT;
	}
#elif defined(INV_NEX)
	if ( err == INV_ERR_OVER_CURRENT ) {
		return MOTOR_ERROR_INV_OVER_CURRENT;
	} else if ( err == INV_ERR_OVER_VOLTAGE ) {
		return MOTOR_ERROR_INV_OVER_VOLTAGE;
	} else if ( err == INV_ERR_OVER_HEAT ) {
		return MOTOR_ERROR_INV_OVER_HEAT;
	} else if ( err == INV_ERR_LOW_VOLTAGE ) {
		return MOTOR_ERROR_INV_LOW_VOLTAGE;
	} else if ( err == INV_ERR_UNKNOWN) {
		return MOTOR_ERROR_INV_ERR;
	} else if ( err == INV_ERR_TIMEOUT ) {
		return MOTOR_ERROR_INV_LOW_VOLTAGE;
	} else if ( err == INV_ERR_CRC ) {
		return MOTOR_ERROR_INV_CRC;
	} else {
		return MOTOR_ERROR_INV_TIMEOUT;
	}
#else
	return err;
#endif
}


/// if inv_start() fails, user can select stop or continue
/// \param seed_flag WHEEL_SPEED_HI, WHEEL_SPEED_LO
/// \return 0 success
int inv_start_with_error_handling(int speed_flag)
{
	int ret = 0;
	int answer = ERR_ANS_STOP;
	int retry = 0;
#define RETRY_COUNT 3

	while(1) {
		retry ++;
		ret = inv_start(speed_flag);

		if ( retry >= RETRY_COUNT ) {
			break;
		}

		if ( ret < 0 ) {
#if defined(INV_HPE7000)
			send_hmc_error_msg(UART_GUI, inverter_status_str);
			send_hmc_err_req(UART_GUI, inverter_error_to_motor(ret));
			recv_hmc_err_ans(UART_GUI, &answer, gui_answer_timeout);
#elif defined(INV_CPE4000)
			enable_uart_handler(UART_GUI);
			send_cpe_motor_err_req(UART_GUI, inverter_error_to_motor(ret));
			recv_cpe_motor_err_ans(UART_GUI, &answer, gui_answer_timeout);
			disable_uart_handler(UART_GUI);
#elif defined(INV_NEX)
			PR("send/recv code not implemented.\n");
#endif

			if ( answer == ERR_ANS_STOP) {
				break;
			}
		} else {
			break;
		}
	}

	if ( ret < 0 ) {
		return -inverter_error_to_motor(ret);
	} 
	return 0;
}

/// wheel start (no error check)
/// \param seed_flag WHEEL_SPEED_HI, WHEEL_SPEED_LO
/// \return 0 success
int inv_start_without_error_handling(int speed_flag)
{
	int freq;
	int ret;

	if ( speed_flag == WHEEL_SPEED_HI ) {
		freq = inv_meta.freq_hi;
	} else {
		freq = inv_meta.freq_lo;
	}

	ret = inv_run(freq);

	if ( ret < 0 ) {
		return -inverter_error_to_motor(ret);
	}
	return ret;

}

/// inverter packet debugging
/// param onoff 1-dump on , 0-dump off
void set_inverter_packet_dump(int onoff)
{
	if ( onoff ) {
		send_inverter_func = send_inverter_debug;
		recv_inverter_func = recv_inverter_debug;
		PR("Inverter packet dump ON\n");
	} else {
		send_inverter_func = send_inverter;
		recv_inverter_func = recv_inverter;
		PR("Inverter packet dump OFF\n");
	}
}
/********** end of file **********/
