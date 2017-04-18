/*!
 * \file epc_frame_data.h
 * \brief
 *
 * frame data 송수신 패킷 생성
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 월  6월 26 14:40:48 KST 2006
 *
*/
#ifndef _EPC_FRAME_DATA_H_
#define _EPC_FRAME_DATA_H_

#include "epc_type_def.h"

// frame data parameter
// 각 필드값은 실제 값과 동일하다 (float 형 그대로 사용할 것)
struct epc_frame_data {
	int data_type; // 0x01 +layout option, 0x02 +edging option, 0x04 + dp option, see EPC_ISO16284_ xxxx 
	int side; // 0 -right, 1-left
	int frame_type; // 0 - metal , 1 - plastic, 2 - optyl, 3 - pattern
	float frame_curve; // 프레임 커브 
	float cir; // 둘레 길이 
	float angle_3d; // not used
	int record_number; // 데이터 개수 (무조건 1440 이어야한다)
	float r[MAX_RECORD_SIZE]; // radius 값 
	float a[MAX_RECORD_SIZE]; // angle 값 
	float fpd;  // fpd 값 

	// 확장 정보 (layout)
	int vision_mode; // vision mode  0-far, 1-bifocal, 2-bifocal(circle)
	float bifocal_offset_h; // bifocal 모드에서 blocking offset
	float bifocal_offset_v;
	float bifocal_dia; // 근용부 크기 (지름)
	float bridge_size; // bridge size
	float single_pd; // single pd
	float delta_y; // delta y

	int blocking_mode; // 0 - boxing, 1 - optical
	int oh_type; // 0 - delta_y, 1- boxed_h, 2- mixed_h

	// 확장 정보 2 (dp, edging option)
	float dp_down; // digital pattern 정보 
	float dp_updown;
	float dp_leftright;
	float dp_radius;
	float dp_percent;
	float dp_rotate;

	int fragile_mode; // 0-off/1-on
	int lens_material; // 0 pl, 1 pc, 2 hi, 3 gl, 4 tri
	int edging_type; // 0 rimless, 1 bevel, 2 grooving

	int polish; // 0-off/1-on
	int sb_front; // 0-off/1-on
	int sb_rear; // 0-off/1-small/2-large

	int bevel_pos_type; // 0-percent, 1-front, 2-rear, 3-bc (bevel/grooving position)
	float bevel_pos_value; // bevel 위치 값 (type  의존)
	float size; // 가공 크기 

	float grooving_depth;
	float grooving_width;
};

int epc_frame_data_to_iso16284(char *buf, struct epc_frame_data *param, int count);
int iso16284_to_epc_frame_data(char *buf, struct epc_frame_data *param, int count);

void epc_frame_data_to_file(char *write_buf, struct epc_frame_data *param);
int file_to_epc_frame_data(char *in_buf, struct epc_frame_data *param, int max_count);

#endif
/********** end of file **********/
