/*!
  \file serial.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Dec 08 20:23:51 KST 2010

*/
#ifndef _SERIAL_H_
#define _SERIAL_H_

int open_serial_port(char *port, char *baud_str);
void close_serial_port(void);

#endif
/********** end of file **********/
