/*!
  \file data_convert.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Oct 05 14:15:47 KST 2011

*/
#ifndef _DATA_CONVERT_H_
#define _DATA_CONVERT_H_

#include <llist.h>


void shift_center_r(float *r, float *a, float delta_x, float delta_y, int record_number);
void shift_center_xy(float *x, float *y, float delta_x, float delta_y, int record_number);


void convert_xy_to_r(float *r, float *a, float *x, float *y, int record_number);
void convert_r_to_xy(float *x, float *y, float *r, float *a, int record_number);
int rearrange_angle_data(float *radius_list, float *angle_list, int max);

struct sort_data {
	int idx;
	struct list_head list;
};

#define SORT_FRAME_DATA_FLAG_RT 0x0
#define SORT_FRAME_DATA_FLAG_XY 0x1
#define SORT_FRAME_DATA_FLAG_ASC 0x0
#define SORT_FRAME_DATA_FLAG_DSC 0x2

int sort_frame_data_core(float *r_list, float *a_list, int max, int flag);

#define SORT_FRAME_DATA(r_list, a_list, max) sort_frame_data_core(r_list, a_list, max, SORT_FRAME_DATA_FLAG_RT)
#define SORT_XY_FRAME_DATA(x_list, y_list, max) sort_frame_data_core(x_list, y_list, max, SORT_FRAME_DATA_FLAG_XY)

void convert_r_to_cartesian(const float *r, const float *a, float *x, float *y, const int record_number);
void convert_r_to_cartesianWithMinMax(const float *r, const float *a, float *x, float *y, const int record_number, int* min_x_idx, int* max_x_idx, int* min_y_idx, int* max_y_idx);
void convert_cartesian_to_r(const float *x, const float *y, float *r, float *a, const int record_number);

float calc_2d_circumference(const float* point_x, const float* point_y, int count);
float calc_3d_circumference(const float* point_x, const float* point_y, const float* height, int count);

#endif
/********** end of file **********/
