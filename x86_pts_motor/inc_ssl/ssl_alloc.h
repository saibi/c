/*!
  \file ssl_alloc.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Tue Feb 15 09:12:04 KST 2011

*/
#ifndef _SSL_ALLOC_H_
#define _SSL_ALLOC_H_

extern void * ssl_alloc;
extern void * ssl_calloc;
extern void * ssl_free;

#define SSL_ALLOC ((void * (*)(unsigned int))ssl_alloc)
#define SSL_CALLOC ((void * (*)(unsigned int, unsigned int))ssl_calloc)
#define SSL_FREE ((void (*)(void *))ssl_free)

void ssl_set_alloc_func(void *func_alloc, void *func_free);
void ssl_set_calloc_func(void *func_calloc);

#endif
/********** end of file **********/
