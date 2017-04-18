#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct epc_drill_data {
	int side;
	int ref;   // reference
	int fside; // feature side
	int mnt; // mounting fixture
	float sx;
	float sy;
	float hole_dia;
	float ex;
	float ey;
	float hole_depth;
	int ftype; // feature type
	int angle_mode;
	float lateral_angle;
	float vertical_angle;
	int group_no;
	int flag;
};

typedef struct hole_info_t {
	struct epc_drill_data epc;

	// group center x, y
	float group_cx;
	float group_cy;

	int drill_opt;
#define DRILL_OPT_HOLE 0
#define DRILL_OPT_SLOT 1
#define DRILL_OPT_HUVITZ_RECT_SLOT 2 
} HOLE_INFO;

#define MAX_RECORD_SIZE 1440

typedef struct drill_meta_data_rec {

	// hdm8000 driller & hpe7800 built-in drill

	float *pattern; // radius
	float *pattern_T; // angle
	float *even_pattern; // radius (even angle)
	float *even_pattern_T; // angle (even angle)
	float *half_pattern; // even_pattern + adaptor / 2
	float *frame_x;
	float *frame_y;

	// [2] 0-front, 1-rear,  [3] 0-adaptor, 1-half ptn, 2-ptn
	short feeler_data[2][3][MAX_RECORD_SIZE]; 

	int count;
	int *data_order;
	HOLE_INFO data[100];

	float frame_change_offset; // 20140624

	int feeler_front_offset;
	int feeler_rear_offset;

	float drill_speed_contour;

} DRILL_META;

typedef struct drill_meta_data_rec2 {

	// hdm8000 driller & hpe7800 built-in drill

	float *pattern; // radius
	float *pattern_T; // angle
	float *even_pattern; // radius (even angle)
	float *even_pattern_T; // angle (even angle)
	float *half_pattern; // even_pattern + adaptor / 2
	float *frame_x;
	float *frame_y;

	// [2] 0-front, 1-rear,  [3] 0-adaptor, 1-half ptn, 2-ptn
	short feeler_data[2][3][MAX_RECORD_SIZE]; 

	int count;
	int *data_order;
	HOLE_INFO *data;

	float frame_change_offset; // 20140624

	int feeler_front_offset;
	int feeler_rear_offset;

	float drill_speed_contour;

} DRILL_META2;

typedef struct task_rec {

	DRILL_META d;
	DRILL_META2 d2;
} TASK;


TASK global_task;

int main(void)
{
	TASK *p;
	int i;

	printf("array -> pointer test\n");

	p = &global_task;

	// alloc

	p->d2.data = (HOLE_INFO *)malloc( sizeof(HOLE_INFO) * 100 );
	if ( p->d2.data == NULL ) 
	{
		printf("insufficient memory.\n");
		return 1;
	}
	printf("p->d2.data = %p\n", p->d2.data);

	for ( i = 0 ; i < 10; i++ ) 
	{
		printf("[%d] array %p, ptr %p, (ptr) %p\n", i, &p->d.data[i].epc, &p->d2.data[i].epc, &(p->d2.data[i].epc));
	}
	return 0;
}

