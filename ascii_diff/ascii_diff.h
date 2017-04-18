#ifndef _ASCII_DIFF_H_
#define _ASCII_DIFF_H_

#define RECORD_ANGLE_DATA "A"
#define RECORD_RADIUS_DATA "R"
#define RECORD_Z_DATA "Z"
#define RECORD_Z_ANGLE_DATA "ZA"

#define BASELINE_MULTIPLIER 1000.0
#define BASELINE_MULTIPLIER_FOR_ANGLE 10000.0
#define BASELINE_MULTIPLIER_FOR_FPD 100.0


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


#define ISO16284_STR_CODE_FS "\x1c"
#define ISO16284_STR_CODE_GS	"\x1d"
#define ISO16284_STR_CODE_ACK "\x06"
#define ISO16284_STR_CODE_NAK "\x15"
#define ISO16284_STR_CODE_CR	"\x0d"
#define ISO16284_STR_CODE_RS	"\x1e"

#define ISO16284_STR_FSEP ";"
#define ISO16284_STR_LSEP "="
#define ISO16284_STR_CSEP ","


int parse_ascii_diff_record(char *first_line, int type, int rev, float *list, int max);

#endif
/********** end of file **********/
