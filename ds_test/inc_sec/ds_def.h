/*!
  \file ds_def.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : 목  7월 18 14:53:13 KST 2013

*/
#ifndef _DS_DEF_H_
#define _DS_DEF_H_

#include <llist.h>

#define DRILL_SHAPE_MAX_RECORD_COUNT 5000
#define DRILL_SHAPE_MIN_RECORD_COUNT 3

#define DRILL_SHAPE_FLAG_MAGIC 		0xC8000000
#define DRILL_SHAPE_FLAG_MAGIC_MASK 	0xff000000
#define DRILL_SHAPE_FLAG_SIZE_MASK	0x000fffff
#define DRILL_SHAPE_FLAG_ALLOCATED	0x00100000

typedef struct drill_shape {
	int flag;

	int record_count;
	float *r_list; // mm
	float *a_list; // radian

	struct list_head list;

	char buf[ZERO_ARRAY_IDX];  
	// define ZERO_ARRAY_IDX 0 or 1 (1 for SDT 2.5) 
} DRILL_SHAPE;


DRILL_SHAPE * alloc_DRILL_SHAPE(int record_count);
int is_valid_DRILL_SHAPE(DRILL_SHAPE *pds);
void free_DRILL_SHAPE(DRILL_SHAPE *pds);
void pr_DRILL_SHAPE(DRILL_SHAPE *pds, int show_item);


typedef struct drill_shape_list {
	int flag;
	struct list_head head;
} DRILL_SHAPE_LIST;


void init_DRILL_SHAPE_LIST(DRILL_SHAPE_LIST *pl);
int is_valid_DRILL_SHAPE_LIST(DRILL_SHAPE_LIST *pl);
int get_DRILL_SHAPE_LIST_count(DRILL_SHAPE_LIST *pl);
int add_DRILL_SHAPE_to_list(DRILL_SHAPE_LIST *pl, DRILL_SHAPE *pds);
DRILL_SHAPE * get_DRILL_SHAPE_from_list(DRILL_SHAPE_LIST *pl, int index);
void free_DRILL_SHAPE_LIST(DRILL_SHAPE_LIST *pl);

#endif 
/********** end of file **********/
