/*!
 * \file debug_support.h
 * \brief
 *
 * for console debugging
 *
 * support functions
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : ±Ý  5¿ù 19 19:26:32 KST 2006
 *
*/

#ifndef _DEBUG_SUPPORT_H_
#define _DEBUG_SUPPORT_H_

void dump_buf(char *buf, int size, char *format, int col);
void hex_dump(char *buf, int size, int max_col);

#endif 
/********** end of file **********/
