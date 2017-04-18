/*!
 * \file epc_edging_param.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 화 5 20  Korea Standard Time 2008
 *
*/
#ifndef _EPC_EDGING_PARAM_H_
#define _EPC_EDGING_PARAM_H_

// 가공 작업 종류 
#define EPC_EP_EDGING 0x01
#define EPC_EP_RETOUCHING 0x02
#define EPC_EP_DRILLING 0x04

#define EPC_EP_DRILL_ONLY 0x08
#define EPC_EP_FEELING_ONLY 0x10
#define EPC_EP_DRILL_RETOUCH 0x20





struct epc_edging_param {
	int side; // r/l 구분 
	int frame_type; // metal/pl/plsoft/pattern
	float circumference; // 둘레길이
	int r_number;
	int a_number;
	int z_number;
	float *r_list; // radius data pointer
	float *a_list; // angle data pointer
	float *z_list; // z data pointer

	int edging_type; // bevel/rimless/grooving 
	int lens_material; // pl/pc/hi/gl/tri
	int fragile_mode; // off/on
	int polish; // off/on
	int sb_front; // off/on
	int sb_rear; // off/small/large 
	int frame_change; // off/on
	int pos_type; // percent/front/rear/bc
	float pos_value; // value
	int clamp_pressure; // value
	float size; // edging size
	float grooving_depth; // value
	float grooving_width; // value
	float sb_front_amount; // value
	float sb_rear_small_amount; // value
	float sb_rear_large_amount; // value
	int flag;
#define EP_FLAG_DEMO_LENS_CURVE 0x01
#define EP_FLAG_FRAME_CURVE 0x02
#define EP_FLAG_DRILL_WRAP 0x04
#define EP_FLAG_HI_POLISH 0x08
#define EP_FLAG_DRILL_QUALITY_HIGH 0x10
#define EP_FLAG_FEELING_OUTSIDE_BEVEL 0x20

	// roughing algorithm (0x40 | 0x80 )
#define EP_FLAG_ROUGH_ALG_NORMAL (0x40 | 0x80) 
#define EP_FLAG_ROUGH_ALG_SPIRAL (0x40)
#define EP_FLAG_ROUGH_ALG_HYBRID (0x80)
#define EP_FLAG_ROUGH_ALG_AXIAL (0x0100)

	// feeling mode : default -> both 
#define EP_FLAG_FEELING_MODE_FRONT 0x0200
#define EP_FLAG_FEELING_MODE_REAR 0x0400

	float frame_curve;
	int vision_mode;
};

// retouch parameter
struct epc_retouch_param {
	int side; // r/l 구분 
	int polish; // off/on
	int clamp_pressure; // value
	float size; // retouch size
	float grooving_depth; // value
	int flag;
};




void make_epc_edging_param_packet(char *buf, char *job_no, struct epc_edging_param *param);
void make_epc_edging_param_raz_packet(char *buf, struct epc_edging_param *param);
int iso16284_to_epc_edging_param(char *buf, char *job_no, int job_max, struct epc_edging_param *param);
void free_epc_edging_param_raw_record(struct epc_edging_param *p);
int parse_epc_retouch_param(char *buf, char *job_no, struct epc_retouch_param *param);

#endif
/********** end of file **********/
