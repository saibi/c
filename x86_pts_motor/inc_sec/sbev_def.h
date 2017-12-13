/*!
  \file sbev_def.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : 2015/06/16 19:21:26 (KST)

*/
#ifndef _SBEV_DEF_H_
#define _SBEV_DEF_H_

#include <llist.h>

#define STEP_BEVEL_MIN_RECORD_COUNT 3
#define STEP_BEVEL_MAX_RECORD_COUNT 1440

#define STEP_BEVEL_FLAG_MAGIC 		0xC8000000
#define STEP_BEVEL_FLAG_MAGIC_MASK 	0xff000000
#define STEP_BEVEL_FLAG_SIZE_MASK	0x000fffff
#define STEP_BEVEL_FLAG_ALLOCATED	0x00100000

typedef struct step_bevel_data {
	int flag;

	int record_count;
	float *r_list; // mm
	float *a_list; // radian

	float front_width; // mm

	struct list_head list; // for step bevel fitting data list (record_count, r_list, a_list)

	char buf[ZERO_ARRAY_IDX];
} STEP_BEVEL_DATA;

STEP_BEVEL_DATA * alloc_STEP_BEVEL_DATA(int record_count);
int is_valid_STEP_BEVEL_DATA(STEP_BEVEL_DATA *pds);
void free_STEP_BEVEL_DATA(STEP_BEVEL_DATA *pds);
void pr_STEP_BEVEL_DATA(STEP_BEVEL_DATA *pds, int show_item);



// 20160412 for step bevel fitting data

typedef struct step_bevel_data_list {
	int flag;
	struct list_head head;
} STEP_BEVEL_DATA_LIST;


void init_STEP_BEVEL_DATA_LIST(STEP_BEVEL_DATA_LIST *pl);
int is_valid_STEP_BEVEL_DATA_LIST(STEP_BEVEL_DATA_LIST *pl);
int get_STEP_BEVEL_DATA_LIST_count(STEP_BEVEL_DATA_LIST *pl);
int add_STEP_BEVEL_DATA_to_list(STEP_BEVEL_DATA_LIST *pl, STEP_BEVEL_DATA *pds);
STEP_BEVEL_DATA * get_STEP_BEVEL_DATA_from_list(STEP_BEVEL_DATA_LIST *pl, int index);
void free_STEP_BEVEL_DATA_LIST(STEP_BEVEL_DATA_LIST *pl);

#endif
/********** end of file **********/
