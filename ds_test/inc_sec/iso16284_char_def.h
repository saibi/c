/*
 * iso16284_char_def.h: Reserved Characters in ISO16284:2001(E)
 * Programmed by Park, JaeHo(jrogue@huvitz.com)
 * Last modification date: 2004/4/4(Sun)
 */

#ifndef _ISO16284_CHAR_DEF_H
#define _ISO16284_CHAR_DEF_H

/* Start of message */
#define CHAR_FS		0x1c

/* End of message */
#define CHAR_GS		0x1d

/* Reserved (XOFF) */
#define CHAR_DC1	0x11

/* Reserved (XON) */
#define CHAR_DC3	0x13

/* Acknowledgement */
#define CHAR_ACK	0x06

/* - Ackowledgement */
#define CHAR_NAK	0x15

/* Escape */
#define CHAR_ESC	0x1B

/* CRC separator */
#define CHAR_RS		0x1E

/* DOS End-of-file marker */
#define CHAR_SUB		0x1A

/* Record Separator */
#ifndef CHAR_CR
#define CHAR_CR		0x0D
#endif
#ifndef CHAR_LF
#define CHAR_LF		0x0A
#endif

/* Field Separator */
#define CHAR_FSEP	';'

/* Label Separator */
#define CHAR_LSEP	'='

/* Reserved */
#define CHAR_RSVD	'@'

/* Code Separator */
#define CHAR_CSEP	','

/* Mandatory record flag */
#define CHAR_MFLAG	'*'

/* Unknown data indicator */
#define CHAR_UNKNOWN	'?'

// added by saibi
// string 처리를 쉽게하기 위한 macro
#define ISO16284_STR_CODE_FS "\x1c"
#define ISO16284_STR_CODE_GS	"\x1d"
#define ISO16284_STR_CODE_ACK "\x06"
#define ISO16284_STR_CODE_NAK "\x15"
#define ISO16284_STR_CODE_CR	"\x0d"
#define ISO16284_STR_CODE_RS	"\x1e"

#define ISO16284_STR_FSEP ";"
#define ISO16284_STR_LSEP "="
#define ISO16284_STR_CSEP ","


#endif
/********** end of file **********/
