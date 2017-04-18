/*!
  \file nsym.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Jul 07 09:11:19 KST 2010

*/
#ifndef _NSYM_H_
#define _NSYM_H_

#include <uthash.h>

typedef struct new_symbol_table_entry_rec {
	char *var_name; // <- key

	char **base; // structure field 를 간접 참조할 때 (ex : working_job->xxxx)
	void *addr;
	int flag;
	int param;
	void *handler;

	UT_hash_handle hh;
} NSYM_ENTRY;

#define NSYM_FLAG_TYPE_MASK 0xf
#define NSYM_FLAG_2D_ARRAY 0x10
#define NSYM_FLAG_RDONLY 0x20

enum nsym_type_enum {
	NSYM_TYPE_INT,
	NSYM_TYPE_FLOAT,
	NSYM_TYPE_BIT,
	NSYM_TYPE_CHAR,
	NSYM_TYPE_SHORT,
	NSYM_TYPE_STR,
	NSYM_TYPE_USER
};

NSYM_ENTRY * nsym_find_entry(char *key);
int nsym_get_entry_value(NSYM_ENTRY *entry, int idx, int second_idx, char *buf, int buf_size);
int nsym_set_entry_value(NSYM_ENTRY *entry, int idx, int second_idx, char *buf);

int nsym_add(char *var_name, void *addr, void *base, int flag, int param, void *handler);
void nsym_delete(char *key);
void nsym_list_symbols(char *regexp, int flag);
int nsym_get(char *val_str, char *buf, int buf_size);
int nsym_set(char *val_str, char *buf);

int nsym_get_flag_value(char *key, int *p_flag);
int nsym_set_flag_value(char *key, int flag);
int nsym_set_flag_bit(char *key, int flag);
int nsym_clear_flag_bit(char *key, int flag);

#define NSYM_ADD( tstr, symname) nsym_add(#symname, &symname, NULL, NSYM_TYPE_ ##tstr, 0, NULL)
#define NSYM_ADD_2D( tstr, symname, sz ) nsym_add(#symname, &symname, NULL, NSYM_TYPE_ ##tstr | NSYM_FLAG_2D_ARRAY, sz, NULL)
#define NSYM_ADD_FLAG( symstr, symvar, mask ) nsym_add(symstr, &(symvar), NULL, NSYM_TYPE_BIT, mask, NULL)
#define NSYM_ADD_STR( symname, sz) nsym_add(#symname, &symname, NULL, NSYM_TYPE_STR, sz, NULL)

#define NSYM_ADD_REF( tstr, symstr, base, struct_name, struct_field) nsym_add(symstr, (void*)offsetof( struct_name, struct_field), &base, NSYM_TYPE_ ##tstr, 0, NULL)
#define NSYM_ADD_REF_STR( sz, symstr, base, struct_name, struct_field) nsym_add(symstr, (void*)offsetof( struct_name, struct_field), &base, NSYM_TYPE_STR, sz, NULL)

#endif 
/********** end of file **********/
