/*!
  \file nib.h
  \brief

  New Console Input buffer using hashtable


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Thu Jul 08 12:09:02 KST 2010

*/
#ifndef _NIB_H_
#define _NIB_H_

#include <uthash.h>

typedef struct input_buffer_rec {
	char *name;
	char *buf;
	int size;
	unsigned int tick;

	UT_hash_handle hh;
} NIB_ENTRY;

NIB_ENTRY * nib_search_by_name(char *filename);
NIB_ENTRY * nib_search_by_ptn(char *ptn, int search_size);
int nib_add(char *name, char *buf, int size);
int nib_del(char *name, int del_flag);
void nib_delall(int del_flag);
int nib_rename(char *org_name, char *new_name);
void nib_list_all(void);
void delete_old_nib_entry(void);
void set_max_nib_entry_count(int count);

#endif
/********** end of file **********/
