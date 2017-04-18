/*
 * iso16284_record_label_def.h: Record Label definition in ISO16284:2001(E)
 * Programmed by Park, JaeHo(jrogue@huvitz.com)
 * Last modification date: 2005/7/21(Thu)
 */

#ifndef _ISO16284_RECORD_LABEL_DEF_H
#define _ISO16284_RECORD_LABEL_DEF_H

/* common enumeration type */

enum COMMON_FRAME_SIDE_ENUM { COMMON_FRAME_SIDE_RIGHT = 0, COMMON_FRAME_SIDE_LEFT };

/* Tracer related record label */
#define RECORD_FEELING_DATA "F"
#define RECORD_ANGLE_DATA "A"
#define RECORD_RADIUS_DATA "R"
#define RECORD_FRAME_TYPE "FTYPE"
#define RECORD_Z_DATA "Z"
#define RECORD_Z_ANGLE_DATA "ZA"


#define FRAME_TYPE_UNDEFINED "0"
#define FRAME_TYPE_PLASTIC "1"
#define FRAME_TYPE_METAL "2"
#define FRAME_TYPE_RIMLESS "3"
#define FRAME_TYPE_OPTYL "3"


/* interface related record label */
#define RECORD_ANSWER_TYPE "ANS"
#define RECORD_CRC_CHECK "CRC"
#define RECORD_DEVICE_TYPE "DEV"
#define RECORD_DO_TYPE "DO"
#define RECORD_JOB_NUMBER "JOB"
#define RECORD_MACHINE_IDENTIFIER "MID"
#define RECORD_MACHINE_NAME "MNAME"
#define RECORD_MACHINE_MODEL_NAME "MODEL"
#define RECORD_REQUEST_TYPE "REQ"
#define RECORD_STATUS_CODE "STATUS"
#define RECORD_TRACE_DATA_FORMAT "TRCFMT"
#define RECORD_VENDOR_IDENTIFIER "VEN"
#define RECORD_Z_TRACE_DATA_FORMAT "ZFMT"

#define RECORD_MACHINE_SW_VER "SWVER"

#define RECORD_EMERGENCY_MODE "EMER"

/* DO */
#define DO_R_VALUE "R"
#define DO_L_VALUE "L"
#define DO_B_VALUE "B"
#define DO_N_VALUE "N"

/* TRCFMT/ZFMT */
#define FMT_FORMAT_ASCII 1
#define FMT_FORMAT_BINARY_ABSOLUTE 2
#define FMT_FORMAT_DIFFERENTIAL 3
#define FMT_FORMAT_PACKED_BINARY 4
#define FMT_FORMAT_ASCII_DIFFERENTIAL 5
#define FMT_FORMAT_ASCII_DIFFERENTIAL_REV 6  

#define FMT_FORMAT_EQUIANGULAR "E"
#define FMT_FORMAT_UNEVENLY_SPACED "U"

#define FMT_FORMAT_R_VALUE "R"
#define FMT_FORMAT_L_VALUE "L"
#define FMT_FORMAT_B_VALUE "B"

#define FMT_FORMAT_TARGET_FRAME "F"
#define FMT_FORMAT_TARGET_PATTERN "P"
#define FMT_FORMAT_TARGET_DEMO "D"


/* request type */
#define REQUEST_TYPE_INITIALIZATION "INI"
#define REQUEST_TYPE_EMERGENCY_INITIALIZATION "ENI"
#define REQUEST_TYPE_FRAME_TRACE_UPLOAD "TRC"
#define REQUEST_TYPE_EDGER_DOWNLOAD "EDG"
#define REQUEST_TYPE_EDGER_UPLOAD "MTR"
#define REQUEST_TYPE_FINISH_BLOCKER_DOWNLOAD "FBK"
#define REQUEST_TYPE_GENERIC_UPLOAD "UPL"
#define REQUEST_TYPE_GENERIC_DOWNLOAD "DNL"
#define REQUEST_TYPE_MAINTENANCE_UPLOAD "MNT"
#define REQUEST_TYPE_ERROR_RESPONSE "ERR"
#define REQUEST_TYPE_INFORMATION_UPLOAD "INF"

/* device type */
#define DEVICE_TYPE_FRAME_TRACE_UPLOAD "TRC"
#define DEVICE_TYPE_EDGER_DOWNLOAD "EDG"
#define DEVICE_TYPE_FINISH_BLOCKER_DOWNLOAD "FBK"
#define DEVICE_TYPE_GENERIC_UPLOAD "UPL"
#define DEVICE_TYPE_GENERIC_DOWNLOAD "DNL"

/* for blocker: reset pattern generator packet of ISO 16284 Annex A */
/* BRGSIZ: bridge size */
#define PRESET_PATTERN_GENERATOR_BRGSIZ "BRGSIZ"

/* Monocular Centration distance */
#define PRESET_PATTERN_GENERATOR_IPD "IPD"

/* Monocular Near Centration distance */
#define PRESET_PATTERN_GENERATOR_NPD "NPD"

/* Frame Center Mode(Private) */
#define PRESET_PATTERN_GENERATOR_P_FCM "P_FCM"
enum P_FCM_ENUM { P_FCM_MIXED, P_FCM_BOXED };

/* Frame Characteristic Mode(Private) */
#define PRESET_PATTERN_GENERATOR_P_FCHM "P_FCHM"
enum P_FDM_ENUM { P_FCHM_FTYP, P_FCHM_DIST };

/* Frame Style Mode(Private) */
#define PRESET_PATTERN_GENERATOR_P_FSM "P_FSM"
enum P_FSM_ENUM { P_FSM_FPD, P_FSM_BRIDGE };

/* Frame XY Mode(Private) */
#define PRESET_PATTERN_GENERATOR_P_FXYM "P_FXYM"
enum P_FXYM_ENUM { P_FXYM_X, P_FXYM_Y, P_FXYM_XY };

/* Frame Resize Mode(Private) */
#define PRESET_PATTERN_GENERATOR_P_FRM "P_FRM"
enum P_FRM_ENUM { P_FRM_XY, P_FRM_CIR };


/* FPD */
#define PRESET_LENS_EDGER_FPD "P_FPD"

/* DBL */
#define PRESET_LENS_EDGER_DBL "P_DBL"

/* right circumference */
#define PRESET_LENS_EDGER_R_CIR "P_R_CIR"

/* left circumference */
#define PRESET_LENS_EDGER_L_CIR "P_L_CIR"

/* right 3d angle */
#define PRESET_LENS_EDGER_R_3D_ANGLE "P_R_3D_ANGLE"

/* left 3d angle */
#define PRESET_LENS_EDGER_L_3D_ANGLE "P_L_3D_ANGLE"


// 20060814 frame curve 필드 추가 
/* right frame curve */
#define PRESET_R_FC "P_R_FC"

/* left frame curve */
#define PRESET_L_FC "P_L_FC"





/* Lens Material */
#define PRESET_LENS_EDGER_P_MA "P_MA"
enum P_MA_ENUM { P_MA_TYPE, P_MA_FRAGILE };

/* Lens Edging Process */
#define PRESET_LENS_EDGER_P_EP "P_EP"
enum P_EP_ENUM { P_EP_TYPE, P_EP_POL };

/* Lens Edging MINUTE Condition */
#define PRESET_LENS_EDGER_P_MC "P_MC"
enum P_MC_ENUM { P_MC_PROCESSING, P_MC_SIZE };

/* Lens Safety Beveling */
#define PRESET_LENS_EDGER_P_SB "P_SB"
enum P_SB_ENUM { P_SB_FRONT, P_SB_REAR, P_SB_BOTH };

/* for motor board: preset lens edger packet of ISO 16284 Annex A */
/* ETYP --> 1: Bevel, 2: Rimless, 3: Groove */
#define PRESET_LENS_EDGER_EDGE_TYPE "ETYP"

enum ETYP_ENUM { ETYP_BEVEL = 1, ETYP_RIMLESS, ETYP_GROOVE };

/* FTYP --> 1: Undefined, 2: Plastic, 3: Metal, 4: Rimless */
#define PRESET_LENS_EDGER_FRAME_TYPE "FTYP"

enum FTYP_ENUM { FTYP_UNDEFINED = 1, FTYP_PLASTIC, FTYP_METAL, FTYP_OPTYL, FTYP_RIMLESS };

/* LMATTYPE --> 0: invalid, 1: Plastic, 2: Poly Carbonate, 3: Glass, 4: Hi-index */
#define PRESET_LENS_EDGER_INTEGER_BASIC_MATERIAL_TYPE "LMATTYPE"

enum LMATTYPE_ENUM { LMATTYPE_INVALID = 0, LMATTYPE_PLASTIC, LMATTYPE_PC,
		LMATTYPE_GLASS, LMATTYPE_HI_INDEX, LMATTYPE_TRI };

/* NOT FRAGILE: 0, FRAGILE: 1 */
#define PRESET_LENS_EDGER_FRAGILE_TYPE "PLEFT"
enum FRAGILE_ENUM { FRAGILE_NORMAL = 0, FRAGILE_APPLIED };

/* POLISH: 0: No Polish, 1: Polish */
#define PRESET_LENS_EDGER_POLISH "POLISH"

enum POLISH_ENUM { POLISH_NO_POLISH = 0, POLISH_POLISH };

/* circumference */
#define PRESET_LENS_EDGER_CIRC "CIRC"

/* circumference size */
#define PRESET_LENS_EDGER_CSIZ "CSIZ"

/* safety beveling depth */
#define PRESET_LENS_EDGER_CBEV_FRONT "SBEVFR"
#define PRESET_LENS_EDGER_CBEV_REAR_SMALL "SBEVRS"
#define PRESET_LENS_EDGER_CBEV_REAR_LARGE "SBEVRL"

/* segment width */
#define PRESET_LENS_EDGER_CWIDTH "SWIDTH"

/* radius supplement */
#define PRESET_LENS_EDGER_R_SUPPLEMENT "R_SUPPLEMENT"

/* grooving depth */
#define PRESET_LENS_EDGER_GROOVING_DEPTH "GR_DEPTH"

/* grooving width */
#define PRESET_LENS_EDGER_GROOVING_WIDTH "GR_WIDTH"

enum GROOVING_KIND_ENUM { GROOVING_KIND_DEPTH, GROOVING_KIND_WIDTH };

/* Safty Beveling: 0: No Front SB, 1: Front SB, 2: No Rear SB, 3: Rear SB, 4: Rear SB strong */
#define PRESET_LENS_EDGER_SB "SB"

enum SB_FRONT_ENUM { SB_NO_FRONT_SB = 1, SB_FRONT_SB };
enum SB_REAR_ENUM { SB_NO_REAR_SB = 10, SB_REAR_SB = 20, SB_REAR_SB_STRONG = 30 };

#define PRESET_LENS_EDGER_FRAME_CHANGE "FC"

enum FC_KIND_ENUM { FC_NON_FC = 0, FC_FC };




/// ez tracing data 용 필드 추가
#define RECORD_BRIDGE_SIZE "BRIDGE_SIZE"
#define RECORD_PD "PD"
#define RECORD_DELTA_Y "DELTA_Y"
#define RECORD_R_DELTA_Y "R_DELTA_Y"
#define RECORD_L_DELTA_Y "L_DELTA_Y"

#define RECORD_R_SINGLE_PD "R_SPD"
#define RECORD_L_SINGLE_PD "L_SPD"

#define RECORD_VISION_MODE "VISION_MODE"
#define RECORD_BIFOCAL_OFFSET_H "BIFOCAL_OFFSET_H"
#define RECORD_BIFOCAL_OFFSET_V "BIFOCAL_OFFSET_V"
#define RECORD_BIFOCAL_DIA "BIFOCAL_DIA"
#define RECORD_BLOCKING_MODE "BLOCKING_MODE"


#define RECORD_LAYOUT "LAYOUT"
#define RECORD_R_LOPT "R_LOPT"
#define RECORD_L_LOPT "L_LOPT"

#define RECORD_R_DP "R_DP"
#define RECORD_L_DP "L_DP"
#define RECORD_R_EOPT "R_EOPT"
#define RECORD_L_EOPT "L_EOPT"


#define RECORD_DATA_TYPE "DATA_TYPE" 


// ez sync 
#define RECORD_EZ_SYNC "EZ_SYNC"


// 20080520 drill data
#define RECORD_DRILL_DATA "DRILL_DATA"
#define RECORD_DRILLE "DRILLE"

// edging param
#define RECORD_EDGING_DATA "EDGING_DATA"
#define RECORD_EDGING_PARAM1 "EDGING_PARAM1"
#define RECORD_EDGING_PARAM2 "EDGING_PARAM2"

#define RECORD_REM "REM" // remarks

#endif
/********** end of file **********/
