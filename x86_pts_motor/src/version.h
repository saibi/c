/*!
  \file version.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : ¸ñ  5 20 10:19:02 KST 2010

*/
#ifndef _VERSION_H_
#define _VERSION_H_

#define MAX_VERSION_STR_LEN 128

extern char gui_version_str[MAX_VERSION_STR_LEN];
extern char version_str[MAX_VERSION_STR_LEN];

void make_version_str(void);
void set_gui_version_str(char *str);

#endif
/********** end of file **********/
