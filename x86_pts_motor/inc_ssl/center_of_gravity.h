/*!
  \file center_of_gravity.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Mon Nov 07 21:34:34 KST 2011

*/
#ifndef _CENTER_OF_GRAVITY_H_
#define _CENTER_OF_GRAVITY_H_

float polygon_area(float *x_list, float *y_list, int n);
void centroid_of_2point(float *x_list, float *y_list, float *p_cx, float *p_cy);
void centroid_of_polygon(float *x_list, float *y_list, int n, float *p_cx, float *p_cy);

#endif
/********** end of file **********/
