/*!
  \file cmd_proc_sym.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Jul 07 17:58:07 KST 2010

*/
#ifndef _CMD_PROC_SYM_H_
#define _CMD_PROC_SYM_H_

int check_array_param(char *param, char *base_name, int *index_value);
int sub_pr_cmd_proc(char *symbol);
int sub_set_cmd_proc(char *symbol, char *value);

void symtab_set_command_handler(char *param, void * args);
void symtab_search_command_handler(char *param, void * args);
void symtab_pr_command_handler(char *param, void *args);

#endif
/********** end of file **********/
