/*!
  \file inv_sim.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Feb 15 09:27:36 KST 2012

*/
#include <stdio.h>


#define DUMP_STAT
#define PR printf

typedef struct _inv_info_rec {
	int trip;
	int freq;
	int cur;
	int dcv;
} INV_INFO;

enum _inverter_error_code_idx {
	INV_ERR_OVER_CURRENT = 2,
	INV_ERR_OVER_VOLTAGE = 3,
	INV_ERR_OVER_HEAT = 4,
	INV_ERR_LOW_VOLTAGE = 5,

	INV_ERR_REPLY_TIMEOUT,
	INV_ERR_TOO_FAST,
	INV_ERR_TIMEOUT,
	INV_ERR_UNKNOWN,
	INV_ERR_CRC,

	MAX_INV_ERR_IDX
};
#define MAX_INV_CMD_LEN (8)

typedef struct _inv_meta_data {
	int type;
	unsigned int stop_tick;
	int flag;
	char ret_msg[MAX_INV_CMD_LEN];

	int freq_hi;
	int freq_lo;
	int req_freq;

	int timeout;
	int normal_dcv;
	int start_dcv;
	int start_interval;
} INV_META;

#define INV_TYPE_220 0
#define INV_TYPE_110 1
#define INV_TYPE_110B 2
#define INV_TYPE_ERR 3

#define INV_FLAG_TX_ISR 0x01
#define INV_FLAG_ABNORMAL_VAL 0x02
#define INV_FLAG_DISABLE 0x04 // do not use inverter error check 
#define INV_FLAG_ENABLE_RCV_CHECK 0x08 // enable return packet check 
#define CRC_RETRY_COUNT 3

#define OVER_VOLT_P 130
#define START_STOP_RETRY_FREQ_P 110
#define MIN_START_FREQ_P 60 // 80 ,  80~120 blocked too long
#define MAX_START_FREQ_P 140 // 120
#define LOW_CUR 2
#define MAX_ZERO_CURRENT 10
#define MAX_LOW_FREQ 5
#define LOW_FREQ_P 30
#define LOW_VOLT_P 50

INV_META inv_meta = {
	INV_TYPE_110B, // type
	0, // stop tick 
	INV_FLAG_DISABLE, // flag
	{0, }, // msg
	20000, // HI
	13000, // LO
	20000, // req freq

	35, // timeout seconds
	330, // normal dcv (220v) 
	330, // start dcv (220v)

	15, // stop-start interval 
};

/// print status
static void pr_stat(INV_INFO *p)
{
	PR("T%d, F%d, C%d, V%d\n", p->trip, p->freq, p->cur, p->dcv);
}

/// chek trip status
/// \param p
/// \return 0 no error
/// \return 1 error occured, but continued
/// \return negative_value inverter error
static int check_trip(INV_INFO *p)
{
	int ret = 0;
	static int low_freq_count = 0;
	static int zero_cur_count = 0;

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
	pr_stat(p);
	return ret;
}

INV_INFO inv_info_list[] = {
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 360 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 2, 360 },
	{ 0, 20000, 9, 332 },
	{ 0, 20000, 0, 314 },
	{ 0, 20000, 1, 309 },
	{ 0, 20000, 1, 333 },
	{ 0, 20000, 0, 350 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 360 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 2, 329 },
	{ 0, 20000, 0, 309 },
	{ 0, 20000, 13, 365 },
	{ 0, 20000, 19, 365 },
	{ 0, 20000, 5, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 362 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 360 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 1, 360 },
	{ 0, 20000, 1, 322 },
	{ 0, 20000, 1, 298 },
	{ 0, 20000, 1, 329 },
	{ 0, 20000, 1, 349 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 13, 336 },
	{ 0, 20000, 0, 317 },
	{ 0, 20000, 12, 356 },
	{ 0, 20000, 19, 366 },
	{ 0, 20000, 7, 362 },
	{ 0, 20000, 4, 362 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 360 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 7, 359 },
	{ 0, 20000, 0, 325 },
	{ 0, 20000, 4, 296 },
	{ 0, 20000, 20, 365 },
	{ 0, 20000, 14, 364 },
	{ 0, 20000, 5, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 360 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 11, 342 },
	{ 0, 20000, 1, 316 },
	{ 0, 20000, 1, 349 },
	{ 0, 20000, 19, 366 },
	{ 0, 20000, 5, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 360 },
	{ 0, 20000, 2, 360 },
	{ 0, 20000, 1, 325 },
	{ 0, 20000, 2, 302 },
	{ 0, 20000, 19, 366 },
	{ 0, 20000, 10, 363 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 360 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 360 },
	{ 0, 20000, 3, 360 },
	{ 0, 20000, 1, 313 },
	{ 0, 20000, 0, 314 },
	{ 0, 20000, 1, 338 },
	{ 0, 20000, 1, 355 },
	{ 0, 20000, 4, 360 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 2, 360 },
	{ 0, 20000, 1, 322 },
	{ 0, 20000, 2, 298 },
	{ 0, 20000, 18, 365 },
	{ 0, 20000, 11, 362 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 360 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 360 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 7, 332 },
	{ 0, 20000, 0, 310 },
	{ 0, 20000, 11, 359 },
	{ 0, 20000, 19, 365 },
	{ 0, 20000, 5, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 2, 359 },
	{ 0, 20000, 0, 319 },
	{ 0, 20000, 0, 301 },
	{ 0, 20000, 0, 328 },
	{ 0, 20000, 0, 347 },
	{ 0, 20000, 1, 360 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 1, 333 },
	{ 0, 20000, 1, 312 },
	{ 0, 20000, 0, 316 },
	{ 0, 20000, 1, 338 },
	{ 0, 20000, 0, 354 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 2, 360 },
	{ 0, 20000, 0, 327 },
	{ 0, 20000, 0, 304 },
	{ 0, 2150, 36, 300 },
	{ 0, 6310, 28, 312 },
	{ 0, 10455, 16, 361 },
	{ 0, 14605, 7, 361 },
	{ 0, 18785, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 4, 361 },
	{ 0, 20000, 3, 360 },
	{ 0, 20000, 3, 361 },
	{ 0, 20000, 3, 360 },
	{ 0, 20000, 2, 360 },
	{ 0, 20000, 1, 334 },
	{ 0, 20000, 1, 310 },


	{ -1, -1, -1, -1 },
};

int main(void)
{
	int i;

	printf("inverter simulation\n");

	for ( i = 0 ; inv_info_list[i].trip != -1 ; i++ ) {
		if ( check_trip(&inv_info_list[i]) < 0 ) {
			printf("error\n");
			break;
		}
	}


	return 0;
}

/********** end of file **********/





