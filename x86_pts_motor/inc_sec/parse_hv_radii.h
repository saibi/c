/*!
  \file parse_hv_radii.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : 2015/06/17 11:51:03 (KST)

*/
#ifndef _PARSE_HV_RADII_H_
#define _PARSE_HV_RADII_H_

struct hv_record_HVxF {
	// HVHF, HVSF common
	int fmt;
	int record_count;
	int side;
	int type;

	// for HVSF
	float front_width; 
};

#define RADII_FMT_NONE 0
#define RADII_FMT_ASCII_ABS 1 
#define RADII_FMT_BIANRY_ABS 2 
#define RADII_FMT_BIANRY_DIFF 3 
#define RADII_FMT_PACKED_BIANRY 4 
#define RADII_FMT_ASCII_DIFF 5 
#define RADII_FMT_ASCII_DIFF_REV 6

#define RADII_TYPE_H 0
#define RADII_TYPE_D 1

#define HVHF_FIELD_COUNT 6
#define HVSF_FIELD_COUNT 7


// parse_hvxf.c
int parse_HVxF(char *value, struct hv_record_HVxF *p);

// parse_ascii_radii.c
int parse_ASCII_radii_records(char *label_str, int fmt, char *first_line, int *radii_list, int radii_count);

// conv_value_list.c
void value_list_2_radius(int *value_list, int record_count, int type, float *r_list);
void value_list_2_angle(int *value_list, int record_count, int type, float *a_list);

#endif
/********** end of file **********/
