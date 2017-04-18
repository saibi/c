/*!
  \file epc_support.h
  \brief
  

  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : 목  7월 18 15:09:22 KST 2013

*/
#ifndef _EPC_SUPPORT_H_
#define _EPC_SUPPORT_H_

void remove_quotation_mark(char *str);
void reform_packet_line(char *buf);
int eliminate_REM_and_get_key(char *line, char *key);

int parse_ASCII_ABS_value(char *line, int *p_list, int max);
int parse_ASCII_DIFF_value(char *line, int *p_list, int max);
int parse_ASCII_DIFF_REV_value(char *line, int *p_list, int max);

float dcs_angle_2_huvitz_rad(float angle);
float huvitz_rad_2_dcs_angle(float rad);
#endif 
/********** end of file **********/
