/*
 * iso16284_record.h: ISO16284 record related header file
 * Written by Park, JaeHo(jrogue@huvitz.com)
 * Last Modification Date: 2004/10/07(Thu)
 */
#ifndef _ISO16284_RECORD_H_
#define _ISO16284_RECORD_H_

#define MAX_LINE_LENGTH 80
#define MAX_DIGIT_RESOLUTION 6

#define INVALID_RECORD_LABEL            -1
#define INVALID_RECORD_SEPARATOR        -2
#define INVALID_LABEL_SEPARATOR         -3
#define INVALID_FIELD_SEPARATOR         -4
#define INVALID_FIELD_VALUE             -5


int compose_ASCII_record(char *record_id, int *src, char *target, int count);
int compose_ASCII_differential_record(char *record_id, int *src, char *target, int count);
int compose_binary_absolute_record(char *record_id, int *src, char *target, int count);
int compose_binary_differential_record(char *record_id, int *src, char *target, int count);
int compose_packed_binary_record(char *record_id, int *src, char *target, int count);

int parse_ASCII_record(char *record_id, char *src, int *target, int len, int count);
int parse_ASCII_differential_record(char *record_id, char *src, int *target, int len, int count);
int parse_binary_absolute_record(char *record_id, char *src, int *target, int len, int count);
int parse_binary_differential_record(char *record_id, unsigned char *src, int *target, int len, int count);
int parse_packed_binary_record(char *record_id, unsigned char *src, int *target, int len, int count);

int unescape_string(char *source, char *target, int len);
int escape_string(char *source, char *target, int len);

#endif
/********** end of file **********/
