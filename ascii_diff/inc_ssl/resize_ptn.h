#ifndef _RESIZE_PTN_H_
#define _RESIZE_PTN_H_

int cal_resize_pattern(float *pattern, float *pattern_T, int record_count, float *pattern_resized, float *pattern_T_resized, float changedSize);

int cal_resize_pattern_to_source(float *pattern, float *pattern_T, int record_count, float changedSize);

int cal_resize_pattern_to_source_ratio( float *pattern, float *pattern_T, int record_count, float ratio );

void cal_resize_xy_pattern_to_source(float* xPoint, float* yPoint, int record_count, float changedSize);

void cal_resize_xy_pattern_to_source_ratio(float* xPoint, float* yPoint, int record_count, float ratio);

#endif
