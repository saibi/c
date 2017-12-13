/*!
 * \file utf8.h
 * \brief
 *
 * EZ utf8 support
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 금  6월 09 11:21:06 KST 2006
 *
*/
#ifndef _UTF8_H_
#define _UTF8_H_



#define SKIP_1 0xFE
#define SKIP_2 0xFF

/// EZ 용 utf8 code
typedef struct utf8_char {
	char ch[8]; // Null terminated string 으로 만들기 위해 충분한 공간 확보
	short len;
	unsigned int ucs_code;
} utf8char;


#define MAX_UTF8_SEQ 6

// utf8 sequence
// UCS code                : bit string
// U-00000000 ~ U-0000007F : 0xxxxxxx
// U-00000080 ~ U-000007FF : 110xxxxx 10xxxxxx
// U-00000800 ~ U-0000FFFF : 1110xxxx 10xxxxxx 10xxxxxx
// U-00010000 ~ U-001FFFFF : 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
// U-00200000 ~ U-03FFFFFF : 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
// U-04000000 ~ U-7FFFFFFF : 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx

#define SEQ_TRAILING_MASK 0xc0 
#define SEQ_TRAILING_VAL 0x80



int utf8_strlen(char *str);
int str_to_utf8char(char *str, utf8char *utf8, int utf8_max, int *err_idx);
int utf8char_to_str(utf8char *utf8, int utf8_len, char *str);
void pr_utf8char(utf8char *utf8);

#endif
/********** end of file **********/
