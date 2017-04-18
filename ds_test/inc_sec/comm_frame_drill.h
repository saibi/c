/*!
 * \file comm_frame_drill.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : ¸ñ 5 29  Korea Standard Time 2008
 *
*/
#ifndef _COMM_FRAME_DRILL_H_
#define _COMM_FRAME_DRILL_H_

#include "epc_comm_frame.h"
#include "epc_drill.h"

int send_comm_frame_data(int uart, char *job_no, struct epc_comm_frame_data *frame, int frame_count, struct epc_drill_data *p_drill, int drill_max);
int send_pure_comm_frame_data(int uart, char * request_type, char *job_no, struct epc_comm_frame_data *frame, int frame_count, struct epc_drill_data *p_drill, int drill_max);
int receive_comm_frame_data(int uart, char *job_no, struct epc_comm_frame_data *frame, int frame_count, struct epc_drill_data **p_drill, int *drill_count);
int request_comm_frame_data_ex(int uart, char *job_no, struct epc_comm_frame_data *frame, int frame_count, struct epc_drill_data **p_drill, int *drill_count);

#endif
/********** end of file **********/
