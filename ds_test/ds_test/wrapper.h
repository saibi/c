/*!
  \file wrapper.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : 수  7월 17 17:13:30 KST 2013

*/
#ifndef _WRAPPER_H_
#define _WRAPPER_H_

#include <stdio.h>
#include <malloc.h>
#include <string.h>

// ssl
#include <error.h>
#include <ssl_string.h>
#include <mem_printf.h>


// sec
#include <iso16284_char_def.h>
#include <iso16284_common.h>

#define SSL_PRINTF printf
#define SSL_ALLOC malloc
#define SSL_FREE free 


#define ISO16284_STR_FSEP ";"

#endif
/********** end of file **********/
