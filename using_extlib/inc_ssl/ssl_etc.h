/*!
 * \file ssl_etc.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : ±Ý 4 04  Korea Standard Time 2008
 *
*/
#ifndef _SSL_ETC_H_
#define _SSL_ETC_H_

#ifndef CONST_PI
#define CONST_PI 3.141592
#endif 
#ifndef CONST_PI_MINUTE
#define CONST_PI_MINUTE 3.1415926536
#endif 


#define SAIBI_ABS( x ) ( (x) < 0 ? -(x) : (x))
#define SAIBI_RAD2DEGREE(rad) ( (rad) * 180.0/CONST_PI )
#define SAIBI_DEGREE2RAD(degree) ( (degree) * CONST_PI/180.0)

// ssl_shift.c
int get_shift_count(int mask);

// ssl_endian.c
int read_little_endian_int(char *buf, int size);

// ssl_round.c
int saibi_round(float x);
int saibi_round2(double x);
float excel_round(float dbVal, int nPlaces /* = 0 */);
double excel_round2(double dbVal, int nPlaces /* = 0 */);

// rad_deg.c
float radian2degree(float radian);
float degree2radian(float degree);


#endif
/********** end of file **********/
