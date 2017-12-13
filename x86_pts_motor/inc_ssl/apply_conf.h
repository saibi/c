/*!
  \file apply_conf.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Tue May 17 18:54:05 KST 2011

*/
#ifndef _APPLY_CONF_H_
#define _APPLY_CONF_H_

#define APPLY_CONF_DUMP_ITEMS 0x01
#define APPLY_CONF_DUMP_TOTAL 0x02


int apply_configuration_file(char *buf, int buf_size);
int apply_configuration_file_ex(char *buf, int buf_size, int dump_flag);

#endif
/********** end of file **********/
