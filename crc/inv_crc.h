/*!
  \file inv_crc.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : 2016/01/11 15:03:00 (KST)

*/
#ifndef _INV_CRC_H_
#define _INV_CRC_H_

void fill_inv_crc(char *msg);
int check_inv_crc(char *msg, int len, int dbg_msg);

#endif
/********** end of file **********/
