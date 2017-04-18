/*!
 * \file int_float.h
 * \brief
 *
 * int 타입으로 실수 값을 사용하기 위한 매크로
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 수  1월 31 15:27:10 KST 2007
 *
*/
#ifndef _INT_FLOAT_H_
#define _INT_FLOAT_H_

#define MIN_INT_FLOAT_PLACE 1
#define MAX_INT_FLOAT_PLACE 9

extern float f_int_float_div_list[MAX_INT_FLOAT_PLACE+1];

#define FLOAT_TO_INT_FLOAT(fvalue, place) (int)((fvalue) * f_int_float_div_list[place])
#define INT_FLOAT_TO_FLOAT(ivalue, place) (float)((ivalue) / f_int_float_div_list[place])

#endif 
/********** end of file **********/
