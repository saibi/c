/*!
  \file symbol_func.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Jul 07 11:41:23 KST 2010

*/
#ifndef _SYMBOL_FUNC_H_
#define _SYMBOL_FUNC_H_

void print_int(void *addr);
void set_int(void *addr, void *value);
void print_float(void *addr);
void set_float(void *addr, void *value);
void print_char(void *addr);
void set_char_int(void *addr, void *value);
void print_string(void *addr, int size);
void set_string(void *addr, int size, void *value);
void print_address(void *addr);
void print_int_bit(void *addr, int bit_mask);
void set_int_bit(void *addr, int bit_mask, void *value);

void use_default_symbol_dump_function(void);
void change_symbol_dump_function(void (*func_addr)(char *, ...));

extern void (*symbol_dump_func)(char *, ...);

#endif
/********** end of file **********/
