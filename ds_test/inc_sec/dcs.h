/*!
 * \file dcs.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 월 2 01  대한민국 표준시 2010
 *
*/
#ifndef _VCA_DCS_H_
#define _VCA_DCS_H_

//#define _DEBUG_VCA_DCS_ // vca dcs debug 

#define _VCA_DCS_PACKED_BINARY_CODE_ // use VCA V3.08 Annex B code


// vca dcs comm options
#define VCA_DCS_OPT_COMPOSE_HUVITZ 0x01

// CFR-4000 용 TRCFMT
#define VCA_DCS_CFR4000_DEFAULT_TRCFMT_4_FRAME "1;1440;U;B;F" // frame 양쪽 전송 
#define VCA_DCS_CFR4000_DEFAULT_TRCFMT_4_FRAME_RIGHT "1;1440;U;R;F" // frame 오른쪽 전송 
#define VCA_DCS_CFR4000_DEFAULT_TRCFMT_4_FRAME_LEFT "1;1440;U;L;F" // frame 왼쪽 전송 
#define VCA_DCS_CFR4000_DEFAULT_TRCFMT_4_PATTERN "1;1440;U;B;P" // pattern 양쪽 전송 (현재는 사용할 수 없다)
#define VCA_DCS_CFR4000_DEFAULT_TRCFMT_4_PATTERN_RIGHT "1;1440;U;R;P" // pattern 오른쪽 전송 
#define VCA_DCS_CFR4000_DEFAULT_TRCFMT_4_PATTERN_LEFT "1;1440;U;L;P" // pattern 왼쪽 전송 



// trcfmt 을 int 로 저장하기 위해
#define VCA_DCS_TRCFMT_COUNT_MASK 0x0000ffff // 레코드 개수
#define VCA_DCS_TRCFMT_FORMAT_MASK 0x007f0000 // 레코드 포맷
#define VCA_DCS_TRCFMT_EVEN_MASK 0x00800000 // 각도 
#define VCA_DCS_TRCFMT_SIDE_MASK 0x03000000 // 사이드
#define VCA_DCS_TRCFMT_TRACE_TYPE_MASK 0x0c000000 // 트레이스 타입

// format 1-ascii, 2-binary absolute, 3-differential, 4-packed binary, (5-ascii diff, 6-ascii diff rev [huvitz only])
#define VCA_DCS_TRCFMT_FORMAT_NONE 0 
#define VCA_DCS_TRCFMT_ASCII 1
#define VCA_DCS_TRCFMT_BINARY_ABSOLUTE 2
#define VCA_DCS_TRCFMT_BINARY_DIFFERENTIAL 3
#define VCA_DCS_TRCFMT_PACKED_BINARY 4 
#define VCA_DCS_TRCFMT_ASCII_DIFFERENTIAL 5 // Huvitz Org
#define VCA_DCS_TRCFMT_ASCII_DIFFERENTIAL_REV 6 // Huvitz (XD) 

#define VCA_DCS_TRCFMT_UNEVEN 0
#define VCA_DCS_TRCFMT_EVEN 1 

#define VCA_DCS_TRCFMT_RIGHT 0
#define VCA_DCS_TRCFMT_LEFT 1
#define VCA_DCS_TRCFMT_BOTH 2

#define VCA_DCS_TRCFMT_TRACE_TYPE_NONE 0
#define VCA_DCS_TRCFMT_FRAME 1
#define VCA_DCS_TRCFMT_PATTERN 2
#define VCA_DCS_TRCFMT_DEMO_LENS 3

#define VCA_DCS_GET_TRCFMT_COUNT(x) ((x) & VCA_DCS_TRCFMT_COUNT_MASK)
#define VCA_DCS_GET_TRCFMT_FORMAT(x) (((x) & VCA_DCS_TRCFMT_FORMAT_MASK) >> 16)
#define VCA_DCS_GET_TRCFMT_EVEN(x) (((x) & VCA_DCS_TRCFMT_EVEN_MASK) ? VCA_DCS_TRCFMT_EVEN : VCA_DCS_TRCFMT_UNEVEN)
#define VCA_DCS_GET_TRCFMT_SIDE(x) (((x) & VCA_DCS_TRCFMT_SIDE_MASK) >> 24)
#define VCA_DCS_GET_TRCFMT_TRACE_TYPE(x) (((x) & VCA_DCS_TRCFMT_TRACE_TYPE_MASK) >> 26)

#define VCA_DCS_MAKE_TRCFMT_INT(fmt, count, even, side, ttype) \
	(((count) & 0xffff) | (((fmt) & 0x7f) << 16) | (((even) & 0x1) << 23) | (((side) & 0x3) << 24) | (((ttype) & 0x3 ) << 26) )


// integer frame type : 5~127 reserved
#define VCA_DCS_FTYP_UNDEFINED 0
#define VCA_DCS_FTYP_PLASTIC 1
#define VCA_DCS_FTYP_METAL 2
#define VCA_DCS_FTYP_RIMLESS 3
#define VCA_DCS_FTYP_OPTYL 4

// type of edge : 5~32 reserved, 33~127 defined between host and device
#define VCA_DCS_ETYP_UNCUT -1
#define VCA_DCS_ETYP_BEVEL 1
#define VCA_DCS_ETYP_RIMLESS 2
#define VCA_DCS_ETYP_GROOVE 3
#define VCA_DCS_ETYP_MINI_BEVEL 4

// 20101220 LTYPE flag 
#define VCA_DCS_LTYPE_SV 0x01 // Single Vision
#define VCA_DCS_LTYPE_NV 0x02 // Near variable focus
#define VCA_DCS_LTYPE_BI 0x04 // Bifocal
#define VCA_DCS_LTYPE_TR 0x08 // Trifocal
#define VCA_DCS_LTYPE_PR 0x10 // Progresive addition
#define VCA_DCS_LTYPE_QD 0x20 // Quodrafocal
#define VCA_DCS_LTYPE_DS 0x40 // Double Segment

#define VCA_DCS_LTYPE_40 0x80 // Trifocal Power 40%
#define VCA_DCS_LTYPE_60 0x0100 // Trifocal Power 60%
#define VCA_DCS_LTYPE_70 0x0200 // Trifocal Power 70%

#define VCA_DCS_LTYPE_CT 0x0400 // Curve Top
#define VCA_DCS_LTYPE_EX 0x0800 // E-line multifocal
#define VCA_DCS_LTYPE_FT 0x1000 // Flat top
#define VCA_DCS_LTYPE_RD 0x2000 // Round

#define VCA_DCS_LTYPE_AS 0x4000 // Aspheric
#define VCA_DCS_LTYPE_AT 0x8000 // Atoric
#define VCA_DCS_LTYPE_LT 0x010000 // Lenticular
#define VCA_DCS_LTYPE_FF 0x020000 // Digitally Surfaced
#define VCA_DCS_LTYPE_SO 0x040000 // Slab off
#define VCA_DCS_LTYPE_OR 0x080000 // Oriented








// material type : 7~127 reserved
#define VCA_DCS_LMATTYPE_UNDEFINED 0
#define VCA_DCS_LMATTYPE_PLASTIC 1
#define VCA_DCS_LMATTYPE_POLYCARBONATE 2
#define VCA_DCS_LMATTYPE_GLASS 3 
#define VCA_DCS_LMATTYPE_PATTERN 4
#define VCA_DCS_LMATTYPE_HI_INDEX 5
#define VCA_DCS_LMATTYPE_TRIVEX 6

// Polishing mode : +128 indicates high lustre
#define VCA_DCS_POLISH_NONE 0
#define VCA_DCS_POLISH_EDGE_AND_PIN_BEVELS 1
#define VCA_DCS_POLISH_PIN_BEVELS_ONLY 2
#define VCA_DCS_POLISH_EDGE_ONLY 3
#define VCA_DCS_POLISH_HIGH_LUSTRE_FLAG 0x80

// pressure
#define VCA_DCS_EPRESS_UNDIFINED 0
#define VCA_DCS_EPRESS_VERY_FRAGILE 1
#define VCA_DCS_EPRESS_SOFT_PRESSURE 2
#define VCA_DCS_EPRESS_MEDIUM_PRESSURE 3
#define VCA_DCS_EPRESS_HARD_PRESSURE 4

// Bevel Position
#define VCA_DCS_BEVP_MANUAL 0
#define VCA_DCS_BEVP_FRONT 1
#define VCA_DCS_BEVP_PERCENT 2
#define VCA_DCS_BEVP_FRAME_CURVE 3
#define VCA_DCS_BEVP_50_50 4
#define VCA_DCS_BEVP_BACK 5
#define VCA_DCS_BEVP_AUTO 7
#define VCA_DCS_BEVP_FREE_FLOAT 10
#define VCA_DCS_BEVP_HUVITZ_BC 6 // 6,8,9 unused

// safety beveling flag
#define VCA_DCS_PINBS_NO 0
#define VCA_DCS_PINBS_HEAVY 1 

// DO
#define VCA_DCS_DO_R 0
#define VCA_DCS_DO_L 1 
#define VCA_DCS_DO_B 2
#define VCA_DCS_DO_N 3


// initialization status code
enum vca_dcs_status_code_list {
	VCA_DCS_STATUS_NO_ERROR = 0,
	VCA_DCS_STATUS_JOB_NOT_FOUND, // 1
	VCA_DCS_STATUS_JOB_IS_PROTECTED,
	VCA_DCS_STATUS_GENERAL,
	VCA_DCS_STATUS_CANNOT_PROCESS_JOB,
	VCA_DCS_STATUS_NEED_INIT,
	VCA_DCS_STATUS_INVALID_JOB_ID,
	VCA_DCS_STATUS_MISSING_RECORD,
	VCA_DCS_STATUS_HOST_ERROR,
	VCA_DCS_STATUS_INCOMPATIBLE,
	VCA_DCS_STATUS_OUT_OF_RANGE,

	VCA_DCS_STATUS_BUSY, // 11
	VCA_DCS_STATUS_OUT_OF_SYNC,
	VCA_DCS_STATUS_INVALID_INIT,
	VCA_DCS_STATUS_AUTOFORMAT_NOT_SUPPORTED,
	VCA_DCS_STATUS_INIT_NOT_SUPPORTED,
	VCA_DCS_STATUS_INVALID_REQ,
	VCA_DCS_STATUS_UNSUPPORTED_TRACING_FORMAT,
	VCA_DCS_STATUS_FORMAT_ERROR,
	VCA_DCS_STATUS_PROCESS_FAILED,

	VCA_DCS_STATUS_NONE_FORMAT = 256,
	VCA_DCS_STATUS_NONE_NUMBER = 512,
	VCA_DCS_STATUS_NONE_RADIUS = 1024,

	VCA_DCS_STATUS_END
};


enum vca_dcs_error_code {
	ERR_VCA_DCS = 1000,

	ERR_VCA_DCS_SEND, // 1001
	ERR_VCA_DCS_RETRY,
	ERR_VCA_DCS_UNKNOWN_CONFIRM,
	ERR_VCA_DCS_CONFIRM_TIMEOUT,
	ERR_VCA_DCS_PACKET_TIMEOUT,
	ERR_VCA_DCS_INVALID_DATA,
	ERR_VCA_DCS_INIT_NOT_SUPPORT,
	ERR_VCA_DCS_STATUS,
	ERR_VCA_DCS_RECORD,
	ERR_VCA_DCS_FORMAT,

	ERR_VCA_DCS_PARAM, // 1011
	ERR_VCA_DCS_DEVICE,

	ERR_VCA_DCS_END
};

enum vca_dcs_packet_code {
	PACKET_VCA_DCS_REQ = 5001,
	PACKET_VCA_DCS_ANS,

	PACKET_VCA_DCS_END
};

#define VCA_DCS_RECORD_LEN 80
#define VCA_DCS_LABEL_LEN 12
#define VCA_DCS_DGR_LEN 16 // drill group string 
#define VCA_DCS_DRILLE_HUVITZ_STR_LEN 20 // huvitz field string

typedef struct vca_dcs_ini_if_rec {
	char DEV[VCA_DCS_RECORD_LEN];
	char VEN[VCA_DCS_RECORD_LEN];
	char MODEL[VCA_DCS_RECORD_LEN];
	char MNAME[VCA_DCS_RECORD_LEN];
	char MID[VCA_DCS_RECORD_LEN];
	char OPERID[VCA_DCS_RECORD_LEN];
	char INFO[VCA_DCS_RECORD_LEN];
	char OMAV[VCA_DCS_RECORD_LEN];
	char DEVICE_TAG[VCA_DCS_RECORD_LEN];
} VCA_DCS_INI_IF;

typedef struct vca_dcs_record {
	char str[VCA_DCS_RECORD_LEN];
} VCA_DCS_RECORD;

typedef struct vca_dcs_label {
	char str[VCA_DCS_LABEL_LEN];
} VCA_DCS_LABEL;




// frame data 


#define VCA_DCS_RECORD_MAX 2048
#define VCA_DCS_RECORD_MIN 200
#define VCA_DCS_SIDE_R 0
#define VCA_DCS_SIDE_L 1


typedef struct vca_dcs_data_record { 
	int trcfmt; // integer TRCFMT
	int record_count;
	int R[VCA_DCS_RECORD_MAX];
	int A[VCA_DCS_RECORD_MAX];

	int zfmt; // integer ZFMT
	int Z[VCA_DCS_RECORD_MAX];
	int ZA[VCA_DCS_RECORD_MAX];
} VCA_DCS_DATA_RECORD;


#define VCA_DCS_FRAME_DATA_SIDE_FLAG_R 0x01
#define VCA_DCS_FRAME_DATA_SIDE_FLAG_L 0x02

typedef struct vca_dcs_drill_record {
	char record[VCA_DCS_RECORD_LEN];
	int flag;
#define VDDF_EYE_SIDE 0x01
#define VDDF_REF_ORG 0x02
#define VDDF_REF_SIDE 0x04
#define VDDF_REF_MNT 0x08
#define VDDF_START_X 0x10
#define VDDF_START_Y 0x20
#define VDDF_DIAMETER 0x40
#define VDDF_END_X 0x80
#define VDDF_END_Y 0x0100
#define VDDF_DEPTH 0x0200
#define VDDF_FEATURE_TYPE 0x0400
#define VDDF_ANGLE_MODE 0x0800
#define VDDF_LATERAL_ANGLE 0x1000
#define VDDF_VERTICAL_ANGLE 0x2000
#define VDDF_MIN_THICK 0x4000
#define VDDF_MAX_THICK 0x8000
#define VDDF_GROUP 0x010000
#define VDDF_HUVITZ 0x020000

	int eye_side; // R, L, B, 0 

	// Permissible combinations : C, CF, CR, EN, ENF, ENR, ET, ETF, ETR, BN, BNF, BNR, BT, BTF, BTR, R
	int ref_org; // C, E, B, R 
	int ref_side; // N, T 
	int ref_mnt; // F, R

	float start_x;
	float start_y;
	float diameter;
	float end_x;
	float end_y;
	float depth;
	int feature_type; // 0,1    , 2
	int angle_mode; // B, F, A
	float lateral_angle;
	float vertical_angle;
	float min_thick; // MINDRL
	float max_thick; // MAXDRL
	char group[VCA_DCS_DGR_LEN];

	char hvstr[VCA_DCS_DRILLE_HUVITZ_STR_LEN];
} VCA_DCS_DRILL_RECORD;

#define VCA_DCS_MAX_HOLE_DEPTH 30.0
#define VCA_DCS_MIN_HOLE_DEPTH -1.0

#define VCA_DCS_DRILL_EYE_SIDE_R 0
#define VCA_DCS_DRILL_EYE_SIDE_L 1
#define VCA_DCS_DRILL_EYE_SIDE_B 2
#define VCA_DCS_DRILL_EYE_SIDE_NONE -1 

#define VCA_DCS_DRILL_REF_CARTESIAN 0
#define VCA_DCS_DRILL_REF_EDGE 1
#define VCA_DCS_DRILL_REF_BOX 2
#define VCA_DCS_DRILL_REF_RELATIVE 3
#define VCA_DCS_DRILL_REF_NONE 0
#define VCA_DCS_DRILL_REF_NASAL 1
#define VCA_DCS_DRILL_REF_TEMPORAL 2
#define VCA_DCS_DRILL_REF_FRONT 1
#define VCA_DCS_DRILL_REF_REAR 2

#define VCA_DCS_DRILL_FTYPE_NONE 0 // same as FTYPE1
#define VCA_DCS_DRILL_FTYPE1 1
#define VCA_DCS_DRILL_FTYPE2 2
#define VCA_DCS_DRILL_FTYPE3_HUVITZ_RECT 3  // for Huvitz RECT SLOT

#define VCA_DCS_DRILL_ANGLE_F 0
#define VCA_DCS_DRILL_ANGLE_B 1
#define VCA_DCS_DRILL_ANGLE_A 2

#define VCA_DCS_MAX_DRILL 100

#define VCA_DCS_DRILL_FORMAT_NEGO_C 0x01
#define VCA_DCS_DRILL_FORMAT_NEGO_E 0x02
#define VCA_DCS_DRILL_FORMAT_NEGO_B 0x04

#define VCA_DCS_DRILLE_HUVITZ_MAGIC "HV"
#define VCA_DCS_DRILLE_HUVITZ_VER 2
// V1 : HV1G1
// V2 : HV2G1R1 support huvitz style rect slot

#define VCA_DCS_DRILLE_HUVITZ_GROUP "G"
#define VCA_DCS_DRILLE_HUVITZ_RECT_SLOT "R1"
#define VCA_DCS_DRILLE_HUVITZ_NORMAL_SLOT "R0"
//#define VCA_DCS_DRILLE_HUVITZ_RETOUCH "R" // deprecated

// N사 LT-1000 모델에서 보내는 데이터를 보고서 작성한 것이므로 나중에 필드 변경 할 것 
typedef struct vca_dcs_frame_data {
	int side_flag; // 0 데이터 없음, 0x01 오른쪽 데이터 있음, 0x02 왼쪽 데이터 있음, 0x03 양쪽 데이터 다 있음

	unsigned int field_flag[4];

	char JOB[VCA_DCS_RECORD_LEN];

	VCA_DCS_DATA_RECORD data[2];

	float CIRC[2];
	float FCRV[2];
	float ZTILT[2];
	float DBL; // bridge size

	int FTYP;
	int ETYP;
	int LTYP[2];
	int LTYPE[2];
	int LMATTYPE[2];

	float PINB[2];
	float FPINB[2];  
	int POLISH;
	float FBFCUP[2]; 
	float FBFCIN[2];

	float AX[2]; // CAB-4000 only
	int EPRESS;

	float IPD[2];
	float OCHT[2];
	float HBOX[2];
	float VBOX[2];
	float MBD[2];

	float MPD; // fpd

	float GDEPTH[2];
	float GWIDTH[2];
	int BEVP[2];
	float BEVC[2];
	float BEVM[2];
	

	// 20100621 
	float NPD[2];
	float SEGHT[2];
	int PINBS[2];

	// CAB-4000 only
	float SPH[2]; 
	float CYL[2]; 
	float PRVM[2];
	float FBOCIN[2];
	float FBOCUP[2];
	float FBSGIN[2];
	float FBSGUP[2];
	float SGOCIN[2];
	float SGOCUP[2];

	int DO;
	float BSIZ[2];
	float CSIZ[2];

	// 20101207
	int drill_count; // 드릴링 데이터 개수 
	VCA_DCS_DRILL_RECORD DRILLE[VCA_DCS_MAX_DRILL];


	// 20110110 Huvitz Data
	float HVDY[2]; 
	int HVOT[2];
	float HVBIDIA[2];
	char HVEF[VCA_DCS_RECORD_LEN];
	char HVDF[VCA_DCS_RECORD_LEN];

	// 20110721
	float SWIDTH[2];

	// 20120215 Huvitz Bevel/Groove data
	char HVBG[2][VCA_DCS_RECORD_LEN];

	// 20121009 Huvitz Bevel Type/ Groove Type (New)
	int HVBT[2];
	float HVBFH[2];
	float HVBRH[2];
	int HVGT[2];
	float HVGSA[2];
	float HVGEA[2];

	// 20130924 Huvitz Groove + Groove 
	float HVGW[2];
	float HVGD[2];

	// 20131017 Huvitz horizontal distance from nasal edge to blocking point
	float HVHDNB[2];

	// 20131118
	float HVDCRV[2]; // demo lens curve, REM=HVDCRV
	int HVDTYP; // DATA_TYPE, REM=HVDTYP

} VCA_DCS_FRAME_DATA;


// slot 0
#define VCA_DCS_FD_FLAG_JOB 		0x00000001
#define VCA_DCS_FD_FLAG_CIRC 		0x00000002
#define VCA_DCS_FD_FLAG_FCRV		0x00000004
#define VCA_DCS_FD_FLAG_ZTILT		0x00000008
#define VCA_DCS_FD_FLAG_DBL		0x00000010
#define VCA_DCS_FD_FLAG_FTYP		0x00000020
#define VCA_DCS_FD_FLAG_ETYP		0x00000040
#define VCA_DCS_FD_FLAG_LTYPE		0x00000080
#define VCA_DCS_FD_FLAG_LMATTYPE	0x00000100
#define VCA_DCS_FD_FLAG_PINB 		0x00000200
#define VCA_DCS_FD_FLAG_FPINB 		0x00000400
#define VCA_DCS_FD_FLAG_POLISH 		0x00000800
#define VCA_DCS_FD_FLAG_FBFCUP 		0x00001000
#define VCA_DCS_FD_FLAG_FBFCIN 		0x00002000
#define VCA_DCS_FD_FLAG_LTYP 		0x00004000
#define VCA_DCS_FD_FLAG_EPRESS  	0x00008000
#define VCA_DCS_FD_FLAG_IPD 		0x00010000
#define VCA_DCS_FD_FLAG_OCHT 		0x00020000
#define VCA_DCS_FD_FLAG_HBOX 		0x00040000
#define VCA_DCS_FD_FLAG_VBOX 		0x00080000
#define VCA_DCS_FD_FLAG_PINBS		0x00100000
#define VCA_DCS_FD_FLAG_MPD 		0x00200000
#define VCA_DCS_FD_FLAG_GDEPTH 		0x00400000
#define VCA_DCS_FD_FLAG_GWIDTH 		0x00800000
#define VCA_DCS_FD_FLAG_BEVP 		0x01000000
#define VCA_DCS_FD_FLAG_BEVC 		0x02000000
#define VCA_DCS_FD_FLAG_BEVM 		0x04000000
#define VCA_DCS_FD_FLAG_Z		0x08000000

// slot 1
#define VCA_DCS_FD_FLAG_NPD 		0x40000001
#define VCA_DCS_FD_FLAG_SEGHT		0x40000002
#define VCA_DCS_FD_FLAG_MBD		0x40000004
#define VCA_DCS_FD_FLAG_SPH		0x40000008
#define VCA_DCS_FD_FLAG_CYL		0x40000010
#define VCA_DCS_FD_FLAG_PRVM		0x40000020
#define VCA_DCS_FD_FLAG_FBOCIN		0x40000040
#define VCA_DCS_FD_FLAG_FBOCUP		0x40000080
#define VCA_DCS_FD_FLAG_FBSGIN		0x40000100
#define VCA_DCS_FD_FLAG_FBSGUP		0x40000200
#define VCA_DCS_FD_FLAG_SGOCIN		0x40000400
#define VCA_DCS_FD_FLAG_SGOCUP		0x40000800
#define VCA_DCS_FD_FLAG_DO		0x40001000
#define VCA_DCS_FD_FLAG_BSIZ		0x40002000
#define VCA_DCS_FD_FLAG_CSIZ		0x40004000
#define VCA_DCS_FD_FLAG_DRLFMT		0x40008000
#define VCA_DCS_FD_FLAG_DRILLE		0x40010000
#define VCA_DCS_FD_FLAG_AX		0x40020000
#define VCA_DCS_FD_FLAG_HVDY		0x40040000 // huvitz field
#define VCA_DCS_FD_FLAG_HVOT		0x40080000 // huvitz field
#define VCA_DCS_FD_FLAG_HVBIDIA		0x40100000 // huvitz field
#define VCA_DCS_FD_FLAG_HVEF 		0x40200000 // huvitz field
#define VCA_DCS_FD_FLAG_SWIDTH		0x40400000
#define VCA_DCS_FD_FLAG_HVDF 		0x40800000 // huvitz field
#define VCA_DCS_FD_FLAG_HVBG 		0x41000000 // huvitz field
#define VCA_DCS_FD_FLAG_HVBT 		0x42000000 // huvitz field
#define VCA_DCS_FD_FLAG_HVBFH 		0x44000000 // huvitz field
#define VCA_DCS_FD_FLAG_HVBRH 		0x48000000 // huvitz field

// slot 2
#define VCA_DCS_FD_FLAG_HVGT		0x80000001 // huvitz field
#define VCA_DCS_FD_FLAG_HVGSA		0x80000002 // huvitz field
#define VCA_DCS_FD_FLAG_HVGEA		0x80000004 // huvitz field
#define VCA_DCS_FD_FLAG_HVGW		0x80000008 // huvitz field
#define VCA_DCS_FD_FLAG_HVGD		0x80000010 // huvitz field
#define VCA_DCS_FD_FLAG_HVHDNB		0x80000020 // huvitz field
#define VCA_DCS_FD_FLAG_HVDCRV		0x80000040 // huvitz field
#define VCA_DCS_FD_FLAG_HVDTYP		0x80000080 // huvitz field


// slot mask
#define VCA_DCS_FD_FLAG_SLOT_MASK 0xc0000000
#define VCA_DCS_FD_FLAG_SLOT_0 0x00000000
#define VCA_DCS_FD_FLAG_SLOT_1 0x40000000
#define VCA_DCS_FD_FLAG_SLOT_2 0x80000000
#define VCA_DCS_FD_FLAG_SLOT_3 0xc0000000







// dcs.c -------------------------------------

extern int vca_dcs_module_ver;
extern char vca_dcs_ver_str[VCA_DCS_RECORD_LEN];
extern int vca_dcs_status_code;

// DEBUG
extern char vca_dcs_test_buf[64*1024];
extern char vca_dcs_test_buf_size;

// 20101025 value changed to prevent slow baud rate 
// retry count & timeout seconds
#define VCA_DCS_CONFIRMATION_RETRY 3 // 3회 재전송
#define VCA_DCS_CONFIRMATION_TIMEOUT 6  // default confirmation timeout 6초
#define VCA_DCS_PACKET_TIMEOUT 12 // default packet timeout 12초

extern int vca_dcs_confirmation_retry;
extern int vca_dcs_confirmation_timeout;
extern int vca_dcs_packet_timeout;
extern int vca_dcs_opt;

void vca_dcs_set_confirm_retry(int count);
void vca_dcs_set_confirm_timeout(int timeout);
void vca_dcs_set_packet_timeout(int timeout);

int vca_dcs_req_ini(int uart);
int vca_dcs_ans_ini(int uart, int status, char *status_str);
int vca_dcs_send_error(int uart);
int vca_dcs_send_req(int uart, char *req_id, char *job_no, VCA_DCS_RECORD *record_list);
int vca_dcs_auto_format_ini(int uart, VCA_DCS_RECORD *inf_list, char *device_tag, VCA_DCS_LABEL *d_list);
int vca_dcs_ans_auto_format_ini(int uart, int status, char *device_tag, char *request_id, VCA_DCS_RECORD *inf_list);
int vca_dcs_preset_ini(int uart, VCA_DCS_RECORD *inf_list);
int vca_dcs_ans_preset_ini(int uart, int status, char *request_id, VCA_DCS_RECORD *inf_list);
int vca_dcs_ans_req(int uart, char *req_id, char *job_no, int status, VCA_DCS_RECORD *record_list);
void vca_dcs_compose_huvitz_field(int onoff);

// dcs_parse.c -----------------------------------
extern VCA_DCS_INI_IF vca_dcs_tracer_ini_rec;
void vca_dcs_int_to_trcfmt(int fmt, char *buf);
int vca_dcs_get_ini_interface_record(char *packet, VCA_DCS_INI_IF * rec);
int vca_dcs_trcfmt_str_to_int(char *value);
int vca_dcs_get_trcfmt_list(char *packet, VCA_DCS_RECORD *trcfmt_list, int trcfmt_max);
int vca_dcs_get_label_list(char *packet, VCA_DCS_LABEL *d_list, int d_max);
int vca_dcs_parse_ans_ini(char *packet, char *status_str);
int vca_dcs_parse_ans_format_ini(char *packet, char *device_tag, char *request_id, char *p_trcfmt, int *p_info, int *p_drlfmt);
int vca_dcs_parse_tracer_req(char *packet, char *job_no);
int vca_dcs_check_tmp_trcfmt(void);
int vca_dcs_parse_frame_data(char *packet, int packet_len, VCA_DCS_FRAME_DATA *p);
int vca_dcs_parse_radii(int trcfmt, char *first_line, VCA_DCS_FRAME_DATA *p);
int vca_dcs_parse_binary_radii(int trcfmt, char *src, int src_len, VCA_DCS_FRAME_DATA *p);
void vca_dcs_int_to_LTYPE_str(int ltype, char *buf);
void vca_dcs_int_to_LTYP_str(int ltyp, char *buf);
int vca_dcs_LTYPE_str_to_int(char *str);
#define vca_dcs_LTYP_str_to_int(str) vca_dcs_LTYPE_str_to_int(str)
int vca_dcs_parse_req_packet(char *packet, char *job_no, char *ven, char *model, char *dev, VCA_DCS_RECORD *trcfmt_list, int trcfmt_max);
int vca_dcs_parse_edger_req(char *packet, char *job_no, char *ven, char *model, VCA_DCS_RECORD *trcfmt_list, int trcfmt_max);
int vca_dcs_frame_data_is_field_flag_set(VCA_DCS_FRAME_DATA *p, unsigned int flag);
void vca_dcs_frame_data_set_field_flag(VCA_DCS_FRAME_DATA *p, unsigned int flag);
void vca_dcs_frame_data_clear_field_flag(VCA_DCS_FRAME_DATA *p, unsigned int flag);
int vca_dcs_get_record_value(char *packet, char *label, char *value);
char * vca_dcs_int_to_do_str(int val);
int vca_dcs_do_str_to_int(char *str);

// dcs_scanner.c ---------------------------------------
int vca_dcs_packet_scanner(char *str, int size, char **scan_pointer);


// dcs_preset_ini.c ------------------------------
extern VCA_DCS_INI_IF vca_dcs_preset_ini_rec;
int vca_dcs_common_preset_ini(int uart, char *dev_str, char *model, char *mid, VCA_DCS_RECORD * p_trcfmt_list, char * request_id, char *p_trcfmt);
#define vca_dcs_tracer_preset_ini(uart, model, mid, p_trcfmt_list, request_id, p_trcfmt) vca_dcs_common_preset_ini(uart, NULL, model, mid, p_trcfmt_list, request_id, p_trcfmt)
#define vca_dcs_edger_preset_ini(uart, model, mid, p_trcfmt_list, request_id, p_trcfmt) vca_dcs_common_preset_ini(uart, "EDG", model, mid, p_trcfmt_list, request_id, p_trcfmt)
#define vca_dcs_blocker_preset_ini(uart, model, mid, p_trcfmt_list, request_id, p_trcfmt) vca_dcs_common_preset_ini(uart, "FBK", model, mid, p_trcfmt_list, request_id, p_trcfmt)
int vca_dcs_recv_preset_ini_from_tracer(int uart, char *request_id);
int vca_dcs_handle_ini_packet(int uart, char *request_id, VCA_DCS_LABEL * d_list, int d_max);

// dcs_auto_ini.c ------------------------------
int vca_dcs_CPE4000_auto_ini(int uart, char *mid, char *request_id, char *p_trcfmt);
int vca_dcs_CPE4000_auto_ini_fmt(int uart, char *mid, char *trcfmt, char *request_id, char *p_trcfmt);
int vca_dcs_CAB4000_auto_ini(int uart, char *mid, char *request_id, char *p_trcfmt);
int vca_dcs_CAB4000_auto_ini_fmt(int uart, char *mid, char *trcfmt, char *request_id, char *p_trcfmt);
int vca_dcs_HPE7000_series_auto_ini(int uart, char *dev, char *mid, char *trcfmt, char *request_id, char *p_trcfmt);
int vca_dcs_HPE7000_auto_ini(int uart, char *mid, char *request_id, char *p_trcfmt);
int vca_dcs_HPE7000_auto_ini_fmt(int uart, char *mid, char *trcfmt, char *request_id, char *p_trcfmt);
int vca_dcs_HPE7000ND_auto_ini_fmt(int uart, char *mid, char *trcfmt, char *request_id, char *p_trcfmt);
void vca_dcs_drill_format_negotiation(char *fmt_str);
void vca_dcs_add_drill_fmt_nego(char fmt);
int vca_dcs_get_drill_fmt_nego_result(void);


// dcs_frame_data.c ------------------------------
char * vca_dcs_make_upload_trcfmt(char *preset_trcfmt, int side, int trace_type);
int vca_dcs_common_frame_data_upload(int uart, char *req_id, char *trcfmt, char *dev_str, VCA_DCS_FRAME_DATA *p);
#define vca_dcs_tracer_frame_data_upload(uart, req_id, trcfmt, p) vca_dcs_common_frame_data_upload(uart, req_id, trcfmt, NULL, p)
int vca_dcs_recv_frame_data_from_tracer(int uart, char *req_packet, char *req_id, VCA_DCS_FRAME_DATA *p);
int vca_dcs_frame_data_download(int uart, char *model, char *job_no, VCA_DCS_FRAME_DATA *p);
int vca_dcs_frame_data_download_ini(int uart, char *req_id, char *trcfmt, char *job_no, VCA_DCS_FRAME_DATA *p);
int vca_dcs_frame_data_download_ex(int uart, char *req_id, char *job_no, VCA_DCS_RECORD *inf_list, VCA_DCS_FRAME_DATA *p);
int vca_dcs_send_ans_frame_data(int uart, char *req_id, char *trcfmt, VCA_DCS_FRAME_DATA *p);

// dcs_device.c ---------------------------
#define VCA_DCS_DEVICE_TRCFMT_LIST_MAX 16
void vca_dcs_init_device_list(void);
int vca_dcs_add_device(char *vendor, char *model, VCA_DCS_RECORD *trcfmt_list, int trcfmt_max, char *default_trcfmt);
int vca_dcs_device_search_trcfmt(char *vendor, char *model, VCA_DCS_RECORD * trcfmt_list, int trcfmt_max, char *p_trcfmt);
VCA_DCS_RECORD * vca_dcs_device_get_trcfmt_list(char *vendor, char *model);
int vca_dcs_get_available_trcfmt(char *model, VCA_DCS_RECORD *req_trcfmt_list, int trcfmt_max, char *trcfmt);
int vca_dcs_change_device_default_trcfmt(char *vendor, char *model, char *default_trcfmt);

// dcs_pr_frame_data.c ---------------------------
void print_vca_dcs_trcfmt_int(int fmt);
void print_vca_dcs_ini_if_rec(VCA_DCS_INI_IF * rec);
void print_VCA_DCS_DATA_RECORD(VCA_DCS_DATA_RECORD *p);
void print_VCA_DCS_FRAME_DATA(VCA_DCS_FRAME_DATA *p, int apply_flag);

// dcs_compose.c --------------------------------
int vca_dcs_is_reserved_char(int ch) ;
int vca_dcs_convert_VCA_DCS_FRAME_DATA_to_bin(char *buf, VCA_DCS_FRAME_DATA *p);

int vca_dcs_compose_ascii_record(char *mem_buf, char *record_id, int *record_list, int record_count);
int vca_dcs_compose_ascii_diff_record(char *mem_buf, char *record_id, int *record_list, int record_count);
int vca_dcs_compose_ascii_diff_rev_record(char *mem_buf, char *record_id, int *record_list, int record_count);
int vca_dcs_compose_binary_absolute_record(char *mem_buf, char *record_id, int *record_list, int record_count);
int vca_dcs_compose_binary_diff_record(char *mem_buf, char *record_id, int *record_list, int record_count);
int vca_dcs_compose_packed_binary_record(char *mem_buf, char *record_id, int *record_list, int record_count);

int vca_dcs_calc_enough_buffer_size_4_VCA_DCS_FRAME_DATA(VCA_DCS_FRAME_DATA *p);





// dcs_huvitz.c ----------------------------------

enum vca_dcs_frame_data_init_type {
	VCA_DCS_FRAME_INIT_CFR_4000_FRAME = 0,
	VCA_DCS_FRAME_INIT_CFR_4000_PATTERN,

	MAX_VCA_DCS_FRAME_INIT
};

//
// huviz frame data 를 VCA_DCS_FRAME_DATA 로 변경하는 방법
// 
// 1. VCA_DCS_FRAME_DATA data; 를 선언한다.
// 2. vca_dcs_frame_data_init_4_huvitz( &data, type) ; 로 자료 구조를 초기화 한다.
// 3. vca_dcs_frame_data_set_radii_4_huvitz() 함수로 frame data 를 설정한다. 좌/우 , Radius, Angle 을 모두 설정하려면 총 4번 호출해야 한다.
// 4. 추가적으로 설정할 필드가 있으면 VCA_DCS_FRAME_DATA 구조체를 보고 직접 data.CIRC[0] = xxxx 식으로 값을 할당한다.
// 5. 사이드 구분은 0 - right, 1 - left 이다. 
//
void vca_dcs_frame_data_init_4_huvitz(VCA_DCS_FRAME_DATA *p, int type, char *job_no, ...);
int vca_dcs_frame_data_set_data_from_huvitz(VCA_DCS_FRAME_DATA *p, int side, float *r_list, float *a_list, int count);
int vca_dcs_frame_data_set_zdata_from_huvitz(VCA_DCS_FRAME_DATA *p, int side, float *z_list, float *za_list, int count);
void vca_dcs_frame_data_add_ztilt(VCA_DCS_FRAME_DATA *p, float r_ztilt, float l_ztilt);
int vca_dcs_frame_data_convert_data_to_huvitz(VCA_DCS_FRAME_DATA *p, int side, float *r_list, float *a_list, int count);
int vca_dcs_frame_data_set_even_data_from_huvitz(VCA_DCS_FRAME_DATA *p, int side, float *r_list, float *a_list, int count);
int vca_dcs_frame_data_set_even_zdata_from_huvitz(VCA_DCS_FRAME_DATA *p, int side, float *z_list, float *za_list, int count);

int vca_dcs_ftyp_to_epc_frame_type(int ftyp);
int epc_frame_type_to_vca_dcs_ftyp(int frame_type);
int epc_edging_type_to_vca_dcs_etyp(int edging_type);
int vca_dcs_etyp_to_epc_edging_type(int etyp);
int epc_lens_material_to_vca_dcs_lmattype(int lens_material);
int vca_dcs_lmattype_to_epc_lens_material(int lmattype);
int epc_polish_to_vca_dcs_polish(int polish);
int vca_dcs_polish_to_epc_polish(int polish);

int vca_dcs_get_frame_count(VCA_DCS_FRAME_DATA *p);
int vca_dcs_get_frame_side(VCA_DCS_FRAME_DATA *p);

int epc_fragile_to_vca_dcs_epress(int fragile);
int vca_dcs_epress_to_epc_fragile(int epress);
int vca_dcs_LTYPE_to_epc_vision_mode(int ltyp);
#define vca_dcs_LTYP_to_epc_vision_mode(val) vca_dcs_LTYPE_to_epc_vision_mode(val)
int epc_vision_mode_to_vca_dcs_LTYPE(int vision_mode);
#define epc_vision_mode_to_vca_dcs_LTYP(val) epc_vision_mode_to_vca_dcs_LTYPE(val)
int set_vca_dcs_bevel_pos_from_huvitz_bp(int epc_bp, float epc_pos_val, int * p_bevp, float *p_bevm, float *p_bevc);
void set_epc_bevel_pos_from_vca_dcs_bevp(int bevp, float bevm, float bevc, int *p_epc_bp, float *p_epc_pos_val);
int vca_dcs_bevp_to_epc_bevel_position(int bevp);
int epc_bevel_position_to_vca_dcs_bevp(int bp);
void set_epc_sb_from_vca_dcs_pinb(float fpinb, float pinb, int pinbs, int *sb_front, int *sb_rear);
int set_vca_dcs_pinb_from_huvitz_sb(int sb_front, int sb_rear, float *fpinb, float *pinb, int *pinbs);

// dcs_calc_bci.c
void dcs_calc_frame_box_from_huvitz(float *r_list, float *a_list, int record_count, float *p_width, float *p_height);
int dcs_gen_DBL_from_MPD(VCA_DCS_FRAME_DATA *p);

// dcs_conv.c
void conv_huvitz_uneven_to_even(float *r, float *a, int record_count, int target_count, float *equi_r, float * equi_a);


// dcs_drill.c
int vca_dcs_parse_DRILLE_record(char *record, VCA_DCS_DRILL_RECORD *p);
int vca_dcs_parse_DRILL_record(char *record, VCA_DCS_DRILL_RECORD *p);
void print_VCA_DCS_DRILL_RECORD(VCA_DCS_DRILL_RECORD *p);

// dcs_drill_compose.c
int vca_dcs_make_DRILLE_record(char *mem_buf, VCA_DCS_FRAME_DATA *p);


// dcs_text.c
int vca_dcs_conv_VCA_DCS_FRAME_DATA_to_text(VCA_DCS_FRAME_DATA *p, char **p_buf);
void vca_dcs_conv_VCA_DCS_FRAME_DATA_set_header(char *header);
void vca_dcs_conv_VCA_DCS_FRAME_DATA_set_footer(char *footer);

// dcs_from_text.c
int vca_dcs_conv_text_to_VCA_DCS_FRAME_DATA(char *buf, int buf_size, VCA_DCS_FRAME_DATA *p);

#include "epc_frame_data.h"

// deprecated 
#if 0
// dcs_convert_epc_frame.c ----------------------------------
int convert_VCA_DCS_FRAME_DATA_to_epc_frame_data(VCA_DCS_FRAME_DATA *src, struct epc_frame_data *dest);
#endif 

// dcs_convert_epc_frame2.c ----------------------------------
int convert_VCA_DCS_FRAME_DATA_to_epc_frame_data2(VCA_DCS_FRAME_DATA *src, struct epc_frame_data *dest);

#if defined(_saibi_edger_comm_library_) || defined(_SPADEWORK_)

#include "epc_comm_frame.h"

// XD 통신 라이브러리용

// deprecated
#if 0
// dcs_convert_epc_comm.c ----------------------------------
int convert_VCA_DCS_FRAME_DATA_to_epc_comm_frame_data(VCA_DCS_FRAME_DATA *src, struct epc_comm_frame_data *dest, int record_count);
#endif

// dcs_convert_epc_comm2.c ----------------------------------
int convert_VCA_DCS_FRAME_DATA_to_epc_comm_frame_data2(VCA_DCS_FRAME_DATA *src, struct epc_comm_frame_data *dest, int record_count);

#endif

#if defined(_saibi_edger_comm_library_) || defined(_SPADEWORK_) || defined(_CAB4000_) || defined(_DICTATOR_EDGER_) || defined(_DICTATOR_DRILL_)
// dcs_convert_epc_drill.c
int calc_epc_drill_data_count_from_VCA_DCS_FRAME_DATA(VCA_DCS_FRAME_DATA *src);
int convert_VCA_DCS_FRAME_DATA_to_epc_drill_data(VCA_DCS_FRAME_DATA *src, struct epc_drill_data *dest, int dest_count);
void vca_dcs_set_epc_drill_default_diameter(float dia);
int convert_epc_drill_data_to_VCA_DCS_FRAME_DATA(struct epc_drill_data *src, int src_count, VCA_DCS_FRAME_DATA *dest);
#endif 





#endif
/********** end of file **********/
