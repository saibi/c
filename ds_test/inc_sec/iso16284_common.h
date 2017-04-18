/*!
 * \file iso16284_common.h
 * \brief
 *
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : ¼ö  7¿ù 05 11:02:53 KST 2006
 *
*/
#ifndef _ISO16284_COMMON_H_
#define _ISO16284_COMMON_H_


struct iso16284_code_to_str { 
	int code;
	char * str;
	int len;
};


extern struct iso16284_code_to_str iso16284_string_table[];
extern char iso16284_CRLF_str[];

int iso16284_string_to_bin(char *src, char *buf, int buf_size);
int get_iso16284_len(char *src);
void change_iso16284_CRLF_str(char *str);


// iso16284_dump.c
void print_iso16284_stream(void *addr);
void print_iso16284_stream_ex(void *addr, int max);
void print_iso16284_bin(void *addr, int len);

#endif
/********** end of file **********/
