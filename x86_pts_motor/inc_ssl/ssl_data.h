/*!
  \file ssl_data.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : 2015/04/10 14:36:53 (KST)

*/
#ifndef _SSL_DATA_H_
#define _SSL_DATA_H_


// data/gen_circle.c
int gen_circle_data(float radius, float *p_r, float *p_a, int count);


// data/internal_div.c
void calc_internal_div_point(float x1, float y1, float x2, float y2, int m, int n, float *px, float *py);

// data/gen_square.c
int gen_square_polygon(float length, float *p_x, float *p_y, int count);

// data/rotate_ptn.c
void rotate_pattern_rad(float *r, float *a, int record_count, float radian_to_rotate);
void rotate_pattern(float *r, float *a, int record_count, float degree_to_rotate);

#endif
/********** end of file **********/
