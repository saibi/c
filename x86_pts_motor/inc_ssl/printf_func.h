/*!
  \file printf_func.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Thu Jul 08 17:08:31 KST 2010

*/
#ifndef _PRINTF_FUNC_H_
#define _PRINTF_FUNC_H_

extern void * ssl_printf;

#define SSL_PRINTF ((void (*)(char *, ...))ssl_printf)

void ssl_set_printf_func(void *func);

#endif
/********** end of file **********/
