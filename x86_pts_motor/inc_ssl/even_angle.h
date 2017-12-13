/*!
  \file even_angle.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Mon Jun 06 17:52:15 KST 2011

*/
#ifndef _EVEN_ANGLE_H_
#define _EVEN_ANGLE_H_

void make_equiangular_data(float *r, float *a, int record_count, int target_count, float *equi_r, float * equi_a);
void make_equiangular_data_with_offset(float *r, float *a, int record_count, int target_count, float *equi_r, float * equi_a, float offset_mm);

#endif
/********** end of file **********/
