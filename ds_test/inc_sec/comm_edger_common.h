/*!
 * \file comm_edger_common.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 월 12 22  대한민국 표준시 2008
 *
*/
#ifndef _COMM_EDGER_COMMON_H_
#define _COMM_EDGER_COMMON_H_

// comm_edger_common.c
int recv_packet_value_string(int uart, int packet_type, char *value_str, int size, int time_out);
int recv_packet_int_value(int uart, int packet_type, int *p_ans, int time_out);


#endif
/********** end of file **********/
