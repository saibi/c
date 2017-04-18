/*!
 * \file epc_text.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 목 12 18  대한민국 표준시 2008
 *
*/
#ifndef _EPC_TEXT_H_
#define _EPC_TEXT_H_

#include "epc_comm_frame.h"
#include "epc_drill.h"

int epc_drill_data_to_text(char **p_file, struct epc_drill_data *p_drill, int drill_count);
int text_to_epc_drill_data(char *p_text, int len, struct epc_drill_data **p_drill);

int comm_frame_to_text(char **p_file, char *job_no, struct epc_comm_frame_data *frame, int frame_count, struct epc_drill_data *p_drill, int drill_count);
int text_to_comm_frame(char *p_file, int len, char *job_no, struct epc_comm_frame_data *frame, struct epc_drill_data **p_drill, int *drill_count);

#endif
/********** end of file **********/
