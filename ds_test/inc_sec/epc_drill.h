/*!
 * \file epc_drill.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 화 5 20  Korea Standard Time 2008
 *
*/
#ifndef _EPC_DRILL_H_
#define _EPC_DRILL_H_

enum epc_drill_side_idx {
	EPC_DRILL_SIDE_R,
	EPC_DRILL_SIDE_L,
	EPC_DRILL_SIDE_BOTH,

	MAX_EPC_DRILL_SIDE_IDX
};

enum epc_drill_reference_idx {
	EPC_DREF_CENTER, // box center 기준 
	EPC_DREF_EDGE, // frame edge 기준 
	EPC_DREF_BOX, // frame box 기준 

	MAX_EPC_DRILL_REFERENCE_IDX
};

enum epc_drill_feature_side_idx {
	EPC_DFSIDE_NASAL, // 코방향 
	EPC_DFSIDE_TEMPORAL, // 귀방향 

	MAX_EPC_DRILL_FEATURE_SIDE_IDX
};

enum epc_drill_mounting_fixture_idx {
	EPC_DMNT_FRONT, // 렌즈 전면
	EPC_DMNT_REAR, // 젠즈 후면

	MAX_EPC_DRILL_MOUNTING_FIXTURE_IDX
};

enum epc_drill_feature_type_idx {
	EPC_DFTYPE_1, // 시작, 끝 중심 좌표
	EPC_DFTYPE_RECT, // 사각 영역 모서리 지정 -> XD 에서는 사각 slot 으로 사용함 (HUVITZ XD 전용)
	EPC_DFTYPE_2_DCS, // VCA DCS 방식의 FEATURE TYPE 2

	MAX_EPC_DRILL_FEATURE_TYPE_IDX
};


enum epc_drill_angle_mode_idx {
	EPC_DANGLE_FRONT_SURFACE, // 전면 수직
	EPC_DANGLE_BACK_SURFACE, // 후면 수직
	EPC_DANGLE_MANUAL, // 사용자 지정

	MAX_EPC_DRILL_ANGLE_MODE_IDX
};
#define EPC_ANGLE_NORMAL_TO_SURFACE 90.0

#define EPC_DGROUP_NONE 0

#define EPC_DRILL_MIN_TILTING 0.0
#define EPC_DRILL_MAX_TILTING 30.0

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


// epc_drill.c
int make_drille_record(char *buf, struct epc_drill_data *p_data, int count);
int parse_a_drille_record(char *buf, struct epc_drill_data *p_data);
int parse_drill_record(char *first_line, struct epc_drill_data **p_drill);

// epc_drill_r.c
int iso16284_to_epc_drill_data(char *buf, char *job_no, int job_no_max, struct epc_drill_data **p_drill);

#endif
/********** end of file **********/
