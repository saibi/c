/*!
 * \file pr_epc_comm_frame.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : ¸ñ 5 29  Korea Standard Time 2008
 *
*/
#ifndef _PR_EPC_COMM_FRAME_H_
#define _PR_EPC_COMM_FRAME_H_

#include "epc_comm_frame.h"

void print_epc_comm_frame_data_field(struct epc_comm_frame_data *p);
void print_epc_comm_frame_raw_data(struct epc_comm_frame_data *p, int flag, int from, int to);

#endif
/********** end of file **********/
