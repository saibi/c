/*!
  \file polygon_zoom.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Thu Feb 02 18:28:38 KST 2012

*/
#ifndef _POLYGON_ZOOM_H_
#define _POLYGON_ZOOM_H_

int calc_polygon_center_width_height(float *x_list, float *y_list, int record_count, float *p_cx, float *p_cy, float *p_width, float *p_height);
int zoom_polygon_xy(float *x_list, float *y_list, int record_count, float width, float height, float delta_x, float delta_y);

#endif
/********** end of file **********/

