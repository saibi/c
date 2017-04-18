/*!
 * \file epc_comm_frame.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 수 5 28  Korea Standard Time 2008
 *
*/
#ifndef _EPC_COMM_FRAME_H_
#define _EPC_COMM_FRAME_H_

#include "epc_drill.h"

struct epc_comm_frame_data {
	int data_type;
	int side;
	int version;

	// frame data
	int r_count;
	float * r;
	int a_count;
	float * a;
	int z_count;
	float *z;

	// frame info
	int frame_type; // 0-metal, 1-pl hard, 2-pl soft, 3-pattern
	float frame_curve;
	float cir;
	float angle_3d;
	float fpd;

	// layout opt
	int vision_mode; // 0-single focus, 1-bifocal, 2-bifocal(circle)
	float bifocal_offset_h;
	float bifocal_offset_v;
	float bifocal_dia;
	float bridge_size;
	float single_pd;
	float delta_y;
	int blocking_mode; // 0-boxing, 1-optical
	int oh_type; // 0-deltaY, 1-boxed_h, 2-mixed_h

	// edging opt
	int fragile_mode; // 0-off, 1-on
	int lens_material; // 0-pl, 1-pc, 2-hi, 3-gl, 4-tri
	int edging_type; // 0-flat, 1-bevel, 2-grooving
	int polish; // 0-off, 1-on
	int sb_front; // 0-off, 1-on
	int sb_rear; // 0-off, 1-small, 2-large
	int pos_type; // 0-percent, 1-front, 2-rear, 3-bc
	float pos_value;
	float size;
	float grooving_depth;
	float grooving_width;

	// 확장 정보, digital pattern 정보 
	float dp_down; 
	float dp_updown;
	float dp_leftright;
	float dp_radius;
	float dp_percent;
	float dp_rotate;

	// 메모리 할당 정보
	int flag;
#define EPC_SALLOC_R 0x10000000
#define EPC_SALLOC_A 0x20000000
#define EPC_SALLOC_Z 0x40000000
};

int epc_comm_frame_data_to_iso16284_v0(char *buf, struct epc_comm_frame_data *param, int count);
int iso16284_to_epc_comm_frame_data_v0(char *buf, struct epc_comm_frame_data *param, int count, struct epc_drill_data **p_drill, int *drill_count);
#endif
/********** end of file **********/
