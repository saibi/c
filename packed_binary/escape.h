#ifndef _ESCAPE_H_
#define _ESCAPE_H_

#define CHAR_FS		0x1c
#define CHAR_GS		0x1d
#define CHAR_DC1	0x11
#define CHAR_DC3	0x13
#define CHAR_ACK	0x06
#define CHAR_NAK	0x15
#define CHAR_ESC	0x1B
#define CHAR_RS		0x1E
#define CHAR_SUB		0x1A
#define CHAR_CR		0x0D
#define CHAR_LF		0x0A
#define CHAR_FSEP	';'
#define CHAR_LSEP	'='
#define CHAR_CSEP	','
#define CHAR_MFLAG	'*'
#define CHAR_UNKNOWN	'?'

int escape(char *dest, char *src, int src_size);
int unescape(char *dest, char *src, int src_size);

#endif
/********** end of file **********/
