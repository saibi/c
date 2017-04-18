/*!
 * \file ssl_string.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 금 4 04  Korea Standard Time 2008
 *
*/
#ifndef _SSL_STRING_H_
#define _SSL_STRING_H_

#ifndef CHAR_CR
#define CHAR_CR		0x0D
#endif 

#ifndef CHAR_LF
#define CHAR_LF		0x0A
#endif


// ssl_ctype.c : c 표준 라이브러리와 충돌을 피하기 위해 이름 앞에 ssl_ 추가 
int ssl_isspace(int c);
int ssl_isdigit(int c);
int ssl_isupper(int c);
int ssl_islower(int c);
int ssl_isalpha(int c);
int ssl_isalnum(int c);

// ssl_trim.c
void ltrim(char *buf);
void rtrim(char *buf);
char *str_first_char(char *buf);

// ssl_space.c
int delete_space(char *buf);
int reduce_space(char *buf);
char * replace_space(char *src, char ch);

// ssl_case.c
void to_upper_str(char *buf);
void to_lower_str(char *buf);

// ssl_token.c
char * extract_token(char *src, char *del, int pos, char *buf, int buf_size);

// ssl_replace.c
void replace_str(char *src, char *change_str, char *change_to, char *buf);
void replace_char(char *str, char src, char dest);
int replace_char2(char *str, char src, char dest);

// ssl_numstr.c
void int_to_bin_str(int value, char *buf);
int hex_char_to_int(char hex_char);
int hatoi(char *hexa_str);
char convert_two_hex_char_to_bin(char hex_char_str[2]);
int get_last_integer_from_str(char *str);
int is_hex_str(char *str);
int str2int(char *str);

// ssl_line.c
int get_line_count(char *str);
char * get_start_line_ptr(char *str, int line_no);
int get_line_from_str(char *src, int line_no, char *buf, int buf_size);
int get_long_line_from_str(char *src, char *buf, int buf_size);
//int get_short_line_from_str(char *src, char *buf, int buf_size);

// ssl_value.c
int get_key_common(char *buf, char *deli, char *key);
int get_value_common(char *buf, char *deli, char *value);
#define get_key(buf, key) get_key_common(buf, "=", key)
#define get_value(buf, value) get_value_common(buf, "=", value) 

// ssl_strrcpy.c
char *strrcpy(char *dest, char *src);

// ssl_strrcat.c
char *strrcat(char *dest, char *src);

// ssl_memint.c
void memset_int(int *mem, int val, int sizeof_mem);
void memcpy_int(int *target, int *src, int sizeof_src);
int find_value_int(int *array, int sizeof_array, int value);

// ssl_memsearch.c
char *memsearch(char *src, int size, char *str);

// ssl_rmemcpy.c
void rmemcpy(char *dest, char *src, int size);



// ssl_param.c
#define PARSE_PARAM_OPT_SKIP_NULL 0x01 // null 일 경우 해당 value skip

void set_parse_param_sep_str(char *sep_str);
int parse_param(char *p_src, char *fmt, ...);
void set_parse_param_opt(int opt);
int get_parse_param_opt(void);

// ssl_param_org.c
int parse_param_org(char *p_src, char *fmt, ...);

// ssl_strdup.c
char * ssl_strdup(char *src);
char * sstrdup(char *src);




#endif
/********** end of file **********/
