/*!
  \file ds_parse.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : 목  7월 18 14:56:07 KST 2013

*/
#ifndef _DS_PARSE_H_
#define _DS_PARSE_H_

#include <ds_def.h>


struct ds_record_HVHF {
	int fmt;
	int record_count;
	int side;
	int type;
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


int iso16284_to_DRILL_SHAPE_LIST(char *buf, DRILL_SHAPE_LIST *pl);



#endif
/********** end of file **********/
