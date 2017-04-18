/*!
  \file cmdarg.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Dec 08 20:09:03 KST 2010

*/
#ifndef _CMDARG_H_
#define _CMDARG_H_

extern char bin_file_path[1024];
extern char port_path[1024];
extern char speed_str[1024];

int proc_cmd_options(int argc, char *argv[]);

#endif
/********** end of file **********/
