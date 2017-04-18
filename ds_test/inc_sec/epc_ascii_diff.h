/*!
 * \file epc_ascii_diff.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : ¼ö 5 21  Korea Standard Time 2008
 *
*/
#ifndef _EPC_ASCII_DIFF_H_
#define _EPC_ASCII_DIFF_H_

enum ascii_diff_type_idx {
	ASCDIFF_R,
	ASCDIFF_A,
	ASCDIFF_Z
};


void to_ascii_diff_format_record(char *buf, int type, int rev, float *record, int record_number);
int parse_ascii_diff_record(char *first_line, int type, int rev, float *list, int max);
int parse_trcfmt(char *fmt, int *record_fmt, int *record_number, char *radius_mode, char *record_side, char *trace_type);

#endif
/********** end of file **********/
