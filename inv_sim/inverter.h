/*!
  \file inverter.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Fri Oct 01 15:19:12 KST 2010

*/

#ifndef _INVERTER_H_
#define _INVERTER_H_

// product type for code sharing
//#define INV_HPE7000 
//#define INV_CPE4000 
//#define INV_NEX




#define WHEEL_SPEED_HI 1
#define WHEEL_SPEED_LO 0

enum _inverter_cmd_idx {
	INV_REQ_DCV, 
	INV_REQ_FREQ,
	INV_REQ_CUR,
	INV_REQ_TRIP,

	INV_CMD_START, 
	INV_CMD_STOP,
	INV_CMD_RESET,

	MAX_INV_CMD_IDX
};

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
#define MAX_INV_REPLY_LEN (7)

#define INV_TYPE_220 0
#define INV_TYPE_110 1
#define INV_TYPE_110B 2
#define INV_TYPE_ERR 3

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

#define INV_CHECK_START 0
#define INV_CHECK_CONT 1
#define INV_CHECK_END 2

extern char inverter_status_str[128];

void set_inverter_frequency(int hi, int lo);
void enable_inverter_check(int stat);
void enable_inverter_rcv_check(int stat);
int get_inverter_frequency(void);
int get_inverter_status(int type);

int inv_stop(void);
int inv_reset(void);
int inv_run(int freq);
int inv_init(void);
int inv_start_ex(int freq);
int inv_start(int speed_flag);
int check_inverter_status(int flag);
int inverter_error_to_motor(int err);
void pr_inverter_meta(void);
int inv_start_with_error_handling(int speed_flag);
int inv_start_without_error_handling(int speed_flag);
void inv_isr_test(int cnt);
void set_inverter_packet_dump(int onoff);
int get_inverter_meta_type(void);
int get_inverter_meta_stat(void);


#endif 
/********** end of file **********/
