/*!
 * \file cib.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 금 4 18  Korea Standard Time 2008
 *
*/
#ifndef _CIB_H_
#define _CIB_H_

#include <llist.h>

// console 입력 버퍼 구조체
struct console_input_buffer {
	char *name;
	char *buf;
	int size;
	struct list_head list;
};

struct console_input_buffer * search_input_buffer_list_by_name(char *name);
struct console_input_buffer * search_input_buffer_list_by_ptn(char *ptn, int ptn_size);
int add_console_input_buffer_list_entry(char *name, char *buf, int size);
int del_console_input_buffer_list_entry(char *name, int del_flag);
int rename_console_input_buffer_list_entry(char *org_name, char *new_name);
void print_console_input_buffer_list(void);

#endif
/********** end of file **********/
