/*!
 * \file epc_type_def.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 목 5 29  Korea Standard Time 2008
 *
*/
#ifndef _EPC_TYPE_DEF_H_
#define _EPC_TYPE_DEF_H_

// 최대 sampling 개수
#ifndef MAX_RECORD_SIZE
#define MAX_RECORD_SIZE 1440
#endif 

// frame side
#ifndef FRAME_SIDE_R
#define FRAME_SIDE_R 0
#define FRAME_SIDE_L 1 
#define MAX_FRAME_SIDE 2
#define MAX_FRAME_SIDE_IDX MAX_FRAME_SIDE
#endif
#define SIDE_R FRAME_SIDE_R
#define SIDE_L FRAME_SIDE_L

#ifndef BASELINE_MULTIPLIER
#define BASELINE_MULTIPLIER 1000.0
#define BASELINE_MULTIPLIER_FOR_ANGLE 10000.0
#define BASELINE_MULTIPLIER_FOR_FPD 100.0
#endif

#define EPC_FRAME_DATA_SECTION_STR "[frame data]"
#define EPC_FRAME_DATA_TYPE_STR "data_type"
#define EPC_FRAME_DATA_SIDE_STR "side"
#define EPC_FRAME_DATA_FRAME_TYPE_STR "frame_type"
#define EPC_FRAME_DATA_FPD_STR "fpd" 
#define EPC_FRAME_DATA_PD_STR "pd" 
#define EPC_FRAME_DATA_SINGLE_PD_STR "single_pd" 
#define EPC_FRAME_DATA_BRIDGE_SIZE_STR "bridge_size" 
#define EPC_FRAME_DATA_DELTA_Y_STR "delta_y" 
#define EPC_FRAME_DATA_CIRCUMFERENCE_STR "circumference"
#define EPC_FRAME_DATA_3D_ANGLE_STR "3d_angle" // not used 
#define EPC_FRAME_DATA_RECORD_NUMBER_STR "record_number"
#define EPC_FRAME_DATA_RADIUS_STR "radius"
#define EPC_FRAME_DATA_ANGLE_STR "angle"

#define EPC_FRAME_DATA_VISION_MODE_STR "vision_mode"
#define EPC_FRAME_DATA_BIFOCAL_OFFSET_H_STR "bifocal_offset_h"
#define EPC_FRAME_DATA_BIFOCAL_OFFSET_V_STR "bifocal_offset_v"
#define EPC_FRAME_DATA_BIFOCAL_DIA_STR "bifocal_dia"
#define EPC_FRAME_DATA_BLOCKING_MODE_STR "blocking_mode"
#define EPC_FRAME_DATA_FRAME_CURVE_STR "frame_curve"
#define EPC_FRAME_DATA_OH_TYPE_STR "oh_type"

#define EPC_FRAME_DATA_DP_DOWN_STR "dp_down"
#define EPC_FRAME_DATA_DP_UPDOWN_STR "dp_updown"
#define EPC_FRAME_DATA_DP_LEFTRIGHT_STR "dp_leftright"
#define EPC_FRAME_DATA_DP_RADIUS_STR "dp_radius"
#define EPC_FRAME_DATA_DP_PERCENT_STR "dp_percent"
#define EPC_FRAME_DATA_DP_ROTATE_STR "dp_rotate"
#define EPC_FRAME_DATA_FRAGILE_MODE_STR "fragile_mode"
#define EPC_FRAME_DATA_LENS_MATERIAL_STR "lens_material"
#define EPC_FRAME_DATA_EDGING_TYPE_STR "edging_type"
#define EPC_FRAME_DATA_POLISH_STR "polish"
#define EPC_FRAME_DATA_SB_FRONT_STR "sb_front"
#define EPC_FRAME_DATA_SB_REAR_STR "sb_rear"
#define EPC_FRAME_DATA_BEVEL_POS_TYPE_STR "bevel_pos_type"
#define EPC_FRAME_DATA_BEVEL_POS_VALUE_STR "bevel_pos_value"
#define EPC_FRAME_DATA_SIZE_STR "size"
#define EPC_FRAME_DATA_GROOVING_DEPTH_STR "grooving_depth"
#define EPC_FRAME_DATA_GROOVING_WIDTH_STR "grooving_width"

// frame type
enum epc_frame_type_idx {
	EPC_FT_METAL,
	EPC_FT_PLASTIC,
	EPC_FT_OPTYL,
	EPC_FT_PATTERN,
	MAX_EPC_FRAME_TYPE_IDX
};

#define EPC_FT_PL_HARD EPC_FT_PLASTIC
#define EPC_FT_HARD_PLASTIC EPC_FT_PLASTIC
#define EPC_FT_PL_SOFT EPC_FT_OPTYL
#define EPC_FT_SOFT_PLASTIC EPC_FT_OPTYL

#define EPC_FT_STR_METAL "metal"
#define EPC_FT_STR_PLASTIC "plastic"
#define EPC_FT_STR_OPTYL "optyl"
#define EPC_FT_STR_PATTERN "pattern"
#define EPC_FT_STR_PL_HARD "hard plastic"
#define EPC_FT_STR_PL_SOFT "soft plastic"


// vision mode
enum epc_vision_mode_idx {
	EPC_VM_FAR,
	EPC_VM_BIFOCAL,
	EPC_VM_BIFOCAL_CIRCLE,

	EPC_VM_EX, // 20090923 ex lens

	MAX_EPC_VISION_MODE_IDX
};


/// PD 타입, near PD 공유
enum epc_pd_type_idx {
	EPC_PT_PD,
	EPC_PT_SINGLE_PD,

	MAX_EPC_PD_TYPE_IDX
};


// epc blocking mode
enum epc_blocking_mode_idx {
	EPC_BOXING_CENTER,
	EPC_OPTICAL_CENTER,
	MAX_EPC_BLOCKING_MODE_IDX
};

#define EPC_BM_BOXING EPC_BOXING_CENTER
#define EPC_BM_OPTICAL EPC_OPTICAL_CENTER



// epc lens material idx : same as lens material idx
enum epc_lens_material_idx {
	EPC_LENS_PL,
	EPC_LENS_PC,
	EPC_LENS_HI,
	EPC_LENS_GL,
	EPC_LENS_TRI,

	MAX_EPC_LENS_MATERIAL_IDX
};


// epc oh type
enum epc_oh_type_idx {
	EPC_OT_DELTA_Y,
	EPC_OT_BOXED_H,
	EPC_OT_MIXED_H,

	MAX_EPC_OH_TYPE_IDX
};

// epc edging type
enum epc_edging_type_idx {
	EPC_ET_RIMLESS, 
	EPC_ET_BEVEL,
	EPC_ET_GROOVING,
	MAX_EPC_ET_IDX
};

enum epc_polish_idx {
	EPC_POLISH_OFF,
	EPC_POLISH_ON,
	MAX_EPC_POLISH_IDX
};
#define EPC_POLISH_HI (EPC_POLISH_ON+1)

// epc bevel position type (grooving)
enum epc_bevel_position_type_idx {
	EPC_BP_PERCENT,
	EPC_BP_FRONT,
	EPC_BP_REAR,
	EPC_BP_BC,
	MAX_EPC_BP_IDX
};
#define EPC_BP_AUTO (EPC_BP_BC + 1)
#define EPC_BP_MANUAL (EPC_BP_BC + 2)

// epc safety bevel front
enum epc_sb_front_idx {
	EPC_SB_FRONT_OFF,
	EPC_SB_FRONT_ON,
	MAX_EPC_SB_FRONT_IDX
};

// epc safety bevel rear 
enum epc_sb_rear_idx {
	EPC_SB_REAR_OFF,
	EPC_SB_REAR_SMALL,
	EPC_SB_REAR_LARGE,
	MAX_EPC_SB_REAR_IDX
};

// epc digital pattern 
enum epc_digital_pattern_idx {
	EPC_DP_DOWN,
	EPC_DP_UPDOWN,
	EPC_DP_LEFTRIGHT,
	EPC_DP_RADIUS,
	EPC_DP_ROTATION,
	EPC_DP_PERCENT,

	MAX_EPC_DP_IDX
};


// epc fragile mode
enum epc_fragile_mode_idx {
	EPC_FM_NOT_FRAGILE,
	EPC_FM_FRAGILE,

	MAX_EPC_FM_IDX
};

// epc frame data 필드 사용 구분 
#define EPC_ISO16284_FRAME_DATA 0x00 // only frame data
#define EPC_ISO16284_LAYOUT 0x01 // layout 정보까지 포함 
#define EPC_ISO16284_EDGING 0x02 // edging 정보까지 포함 
#define EPC_ISO16284_DP 0x04 // digital pattern 정보 포함
#define EPC_ISO16284_R_BLOCKED 0x10 // for auto blocker blocker : side 정보 
#define EPC_ISO16284_L_BLOCKED 0x20 

// device id 추가 
#define EPC_ISO16284_DEVICE_MASK 0x0f00
#define EPC_ISO16284_CFR_4000 0x0100
#define EPC_ISO16284_CFR_3000 0x0200
#define EPC_ISO16284_CAB_4000 0x0300
#define EPC_ISO16284_CPE_4000 0x0400
#define EPC_ISO16284_CPE_3000 0x0500
#define EPC_ISO16284_HPE_7000 0x0600 // 20100304 HEX -> HPE 로 변경 
#define EPC_ISO16284_OTHER_TRACER 0x0700 // 20100304 VCA DCS 프로토콜로 인식할 수 있는 다른 회사 tracer 장비 
#define EPC_ISO16284_OTHER_BLOCKER 0x0800 // 20100317 VCA DCS 프로토콜로 인식할 수 있는 다른 회사 자동 blocker 장비 

#define EPC_ISO16284_HBK_7000 0x0900 // 20100317 신제품 추가
#define EPC_ISO16284_NEX_TRACER 0x0a00 
#define EPC_ISO16284_NEX_BLOCKER 0x0b00 
#define EPC_ISO16284_NEX_MAIN 0x0c00 
#define EPC_ISO16284_NEX_DRILL 0x0d00 




#define EPC_BLOCKING_DATA (EPC_ISO16284_LAYOUT) // blocking 할때 
#define EPC_EDGING_DATA ( EPC_ISO16284_LAYOUT | EPC_ISO16284_EDGING) // auto blocker 에서 edger 로 보낼 때 

// 고급형과 호환을 위해 한 라인에 80 character 가 넘지않도록 한다.
#define EXCELON_COMM_LINE_LEN 70 // 안전빵으로 기준을 70 character 로 지정


// R -> L loop
#define FOR_EACH_SIDE( side_idx_variable ) for ( side_idx_variable = FRAME_SIDE_R; side_idx_variable <= FRAME_SIDE_L; side_idx_variable ++ ) 

#define FRAME_DATA_COPY(ptarget, psrc, pcount) memcpy((char*)(ptarget), (char*)(psrc), sizeof(float) * (pcount))


#endif
/********** end of file **********/
