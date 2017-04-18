/*!
 * \file script.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 금 10 31  대한민국 표준시 2008
 *
*/
#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include <llist.h>

#define SCRIPT_IDENTIFIER "SCRIPT"
#define SCRIPT_START "{"
#define SCRIPT_END "}"

#define MAX_SCRIPT_NAME_LEN 64 // including Null character


struct script_entry {
	char name[MAX_SCRIPT_NAME_LEN];
	struct list_head list;
	char buf[ZERO_ARRAY_IDX];
};


extern struct list_head command_script_list;


int add_file_to_script_list(char *file);
int delete_script(char *name);
struct script_entry * find_script(char *name);
void show_script_list(void);

#endif
/********** end of file **********/

