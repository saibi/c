/*!
  \file nib_file.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Mon May 16 20:25:39 KST 2011

*/
#ifndef _NIB_FILE_H_
#define _NIB_FILE_H_

int add_file_to_nib(char *name, char *buf, int size);
int get_file_from_nib(char *filename, char **pbuf, int *psize);
int del_file_in_nib(char *filename);


#endif 
/********** end of file **********/
