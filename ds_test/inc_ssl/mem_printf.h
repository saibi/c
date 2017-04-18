/*!
 * \file mem_printf.h
 * \brief
 *
 * memory printf
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : ±Ý  6¿ù 23 19:46:41 KST 2006
 *
*/

#ifndef _MEM_PRINTF_H_
#define _MEM_PRINTF_H_

#define MAX_MEM_GET_LINE_SEP_STR_LEN 8

extern char *mem_printf_ptr;
extern char mem_get_line_sep_str[MAX_MEM_GET_LINE_SEP_STR_LEN];
extern char *mem_get_line_internal_cursor;

void mem_printf(char *buf, char *fmt, ...);
void mem_printf_cont(char *fmt, ...);
void mem_putch(char *buf, int ch);
void mem_putch_cont(int ch);
void mem_puts(char *buf, char *str);
void mem_puts_cont(char *str);
int mem_get_line(char *src_buf, char *buf, int buf_len);
int mem_unget_line(char *src_buf, char *buf);
void mem_printf_eat_LF(int stat);

#define GET_MEM_PRINTF_BUF_PTR() (mem_printf_ptr)
#define SET_MEM_PRINTF_BUF_PTR(p) do { mem_printf_ptr = p; } while(0)
#define GET_MEM_GET_LINE_SEP_STR() (mem_get_line_sep_str)
#define SET_MEM_GET_LINE_SEP_STR(pstr) do { strncpy(mem_get_line_sep_str, pstr, MAX_MEM_GET_LINE_SEP_STR_LEN); } while(0)
#define GET_MEM_GET_LINE_BUF_PTR() (mem_get_line_internal_cursor)


#endif
/********** end of file **********/
