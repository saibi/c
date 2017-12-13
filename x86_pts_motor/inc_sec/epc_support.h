/*!
  \file epc_support.h
  \brief
  

  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : 목  7월 18 15:09:22 KST 2013

*/
#ifndef _EPC_SUPPORT_H_
#define _EPC_SUPPORT_H_

// remove_quot.c
void remove_quotation_mark(char *str);

// reform.c
void reform_packet_line(char *buf);

// eliminate_rem.c
int eliminate_REM_and_get_key(char *line, char *key);

// parse_asc_abs.c
int parse_ASCII_ABS_value(char *line, int *p_list, int max);

// parse_asc_diff.c
int parse_ASCII_DIFF_value(char *line, int *p_list, int max);

// parse_asc_diff_rev.c
int parse_ASCII_DIFF_REV_value(char *line, int *p_list, int max);

// dcs_angle.c
float dcs_angle_2_huvitz_rad(float angle);

// huvitz_rad.c
float huvitz_rad_2_dcs_angle(float rad);

// search_hv_key.c
char * search_hv_key(char *rem_line);

#endif 
/********** end of file **********/
