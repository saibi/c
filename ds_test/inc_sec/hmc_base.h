/*!
 * \file hmc_base.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 금 7 25  대한민국 표준시 2008
 *
*/
#ifndef _HMC_BASE_H_
#define _HMC_BASE_H_

//
// 20091012 스트링 만들때 유의사항
//   packet scanner 에서 strstr() 함수를 사용하기 때문에 전체 string 이 포함되는 일이 없도록 한다.
//
//
// 환경설정 값 통신용 
#define PL_HMC_SESSION "HMsession"
#define PL_HMC_CALIBRATION "HMcalib"
#define PL_HMC_ROTATION_LIMIT "HMrlimit"
#define PL_HMC_ROTATION_SPEED "HMrspeed"
#define PL_HMC_WHEEL_SETTING "HMwheelset"
#define PL_HMC_SIZE_ADJ "HMsizeadj"
#define PL_HMC_MARGIN_ADJ "HMmarginadj"
#define PL_HMC_ADDITIONAL_MARGIN_ADJ "HMaddmarginadj"
#define PL_HMC_AXIS_ADJ "HMaxisadj"
#define PL_HMC_BEVEL_ADJ "HMbeveladj"
#define PL_HMC_SB_ADJ "HMsbadj"
#define PL_HMC_GROOVE_ADJ "HMgrooveadj"
#define PL_HMC_FACTORY_SET1 "HMfs1"
#define PL_HMC_FACTORY_SET2 "HMfs2"
#define PL_HMC_FACTORY_SET3 "HMfs3"
#define PL_HMC_CLAMP_PRESSURE "HMcpr"
#define PL_HMC_DRILL_ADJ "HMdrilladj"
#define PL_HMC_DRILL_ADJ2 "HMdrillADJ2"
#define PL_HMC_DRILL_ADJ3 "HMdadj3"

// motor control ( gui <-> motor)
#define PL_HMC_INIT "HMinit"
#define PL_HMC_VER "HMver"
#define PL_HMC_START_JOB "HMstartjob"
#define PL_HMC_RETOUCH_PARAM "HMretouch"
#define PL_HMC_WORK_PROGRESS "HMwps"
#define PL_HMC_WINDOW "HMwnd"
#define PL_HMC_CALIB_ANSWER "HManscalib"
#define PL_HMC_CONTROL "HMcontrol"
#define PL_HMC_REQ_SENSOR_STATUS "HMreqss"
#define PL_HMC_ANS_SENSOR_STATUS "HMansss"
#define PL_HMC_BUSY_STATUS "HMbusy"

#define PL_HMC_LIST_HEADER "HMlistheader"
#define PL_HMC_LIST_VAL "HMlistval"

#define PL_HMC_ERR_MSG "HMerrmsg"


// cpe-4000 compatible label
#define PL_HMC_CLAMP "C_CLAMP"
#define PL_HMC_ERROR "C_ERROR"
#define PL_HMC_PROGRESS_MODE "C_PROGRESS_MODE"
#define PL_HMC_ERR_REQ "C_ERR_REQ"
#define PL_HMC_ERR_ANS "C_ERR_ANS"


// 경고음 처리를 위한 (motor 보드에 buzzer 없음)
#define PL_HMC_BEEP "BEEP"



//
// packet ascii string 
// 

// motor 초기화 %d 는 emergency flag
#define PFMT_MOTOR_INIT_i \
	"<FS>" \
	PL_HMC_INIT "=%d<CR>" \
	"<GS>"

// motor S/W version
#define PFMT_MOTOR_VER_s \
	"<FS>" \
	PL_HMC_VER "=%s<CR>" \
	"<GS>"


// PACKET_HMC_START_JOB
#define PFMT_HEX_MOTOR_START_JOB_iij \
	"<FS>" \
	PL_HMC_START_JOB "=%d;%d<CR>" \
	"JOB=%s<CR>" \
	"<GS>"

// 20090617 기능 확장 (추후 기능 업그레이드를 위해 string 필드 추가함)
#define PFMT_HEX_MOTOR_START_JOB_EXT_iisj \
	"<FS>" \
	PL_HMC_START_JOB "=%d;%d;%s<CR>" \
	"JOB=%s<CR>" \
	"<GS>"

#define PFMT_HEX_MOTOR_WPS_s \
	"<FS>" \
	PL_HMC_WORK_PROGRESS "=%s<CR>" \
	"<GS>"


// PACKET_HMC_CTRL_MOTOR
#define PFMT_HEX_MOTOR_CONTROL_i \
	"<FS>" \
	PL_HMC_CONTROL "=%d<CR>" \
	"<GS>"

// PACKET_HMC_CTRL_MOTOR 
#define PFMT_HEX_MOTOR_CONTROL_M_s \
	"<FS>" \
	PL_HMC_CONTROL "=%s<CR>" \
	"<GS>"

// PACKET_HMC_REQ_SENSOR_STATUS, // sensor 상태 요청
#define PFMT_HEX_MOTOR_SENSOR_i \
	"<FS>" \
	PL_HMC_REQ_SENSOR_STATUS "=%d<CR>" \
	"<GS>"

// PACKET_HMC_ANS_SENSOR_STATUS, // sensor 상태 전송 
#define PFMT_HEX_MOTOR_SENSOR_R_s \
	"<FS>" \
	PL_HMC_ANS_SENSOR_STATUS "=%s<CR>" \
	"<GS>"

#define PFMT_HEX_MOTOR_SENSOR_R_all \
	"<FS>" \
	PL_HMC_ANS_SENSOR_STATUS "=%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d<CR>" \
	"<GS>"
                                                                                // 20130617 add clamp current 


// PACKET_HMC_BUSY_STATUS, // motor busy/idle 상태 전송 
#define PFMT_HEX_MOTOR_BUSY_STATUS_i \
	"<FS>" \
	PL_HMC_BUSY_STATUS "=%d<CR>" \
	"<GS>"




// hex test mode 
#define MK_HMC(ctl, op, param) ( (((ctl) & 0xff) << 24) | (((op) & 0xff) << 16) | ((param) & 0xffff) )

#define GET_CTL_FROM_HMC(val) (((unsigned int)((val) & 0xff000000))>>24)
#define GET_OP_FROM_HMC(val) (((unsigned int)((val) & 0x00ff0000))>>16)
#define GET_PARAM_FROM_HMC(val) ((unsigned int)((val) & 0xffff))


enum hex_motor_control_idx {
	HEX_CTL_RESERVED,
	HEX_CTL_X,
	HEX_CTL_Y,
	HEX_CTL_R,
	HEX_CTL_FEELER,
	HEX_CTL_SBG,
	HEX_CTL_MAIN_MOTOR,
	HEX_CTL_PUMP1,
	HEX_CTL_PUMP2,
	HEX_CTL_DRILL_Y,
	HEX_CTL_DRILL_T,
	HEX_CTL_WINDOW,
	HEX_CTL_CLAMP,
	HEX_CTL_EDGER, // edger 전체 

	MAX_HEX_CTL_IDX
};

enum hex_motor_op_idx {
	HEX_OP_RESERVED,
	HEX_OP_INIT,
	HEX_OP_ON, 
	HEX_OP_OFF,
	HEX_OP_ORG,
	HEX_OP_END,
	HEX_OP_UP, 
	HEX_OP_DOWN, 
	HEX_OP_MOVE,
	HEX_OP_ROTATE, 
	HEX_OP_STOP, 

	HEX_OP_CALIB, 
	HEX_OP_AGING,
	HEX_OP_SLEEP,
	HEX_OP_WHEEL_DRESSING,
	HEX_OP_REPLACE_DRILL_BIT,
	HEX_OP_MODE_CHG,
	HEX_OP_SET_DRILL_BIT_DIA,
	HEX_OP_REQ_CALIB_DATA,
	HEX_OP_CHECK_CUR,

	MAX_HEX_OP_IDX
};

enum op_calib_param_idx {
	HMC_CALIB_PARAM_SIZE,
	HMC_CALIB_PARAM_FEELER,
	HMC_CALIB_PARAM_SBG,
	HMC_CALIB_PARAM_DRILL,
	HMC_CALIB_PARAM_SB, // 각각 따로 캘리브레이션 할 경우를 대비해 
	HMC_CALIB_PARAM_GRV,

	MAX_OP_CALIB_PARAM_IDX
};

enum op_wheel_dressing_param_idx {
	HMC_WHEEL_DRESSING_PARAM_ROUGH_GL,
	HMC_WHEEL_DRESSING_PARAM_FIN,
	HMC_WHEEL_DRESSING_PARAM_POL,
	HMC_WHEEL_DRESSING_PARAM_SB_LEFT,
	HMC_WHEEL_DRESSING_PARAM_SB_RIGHT,
	HMC_WHEEL_DRESSING_PARAM_ROUGH_PL,
	HMC_WHEEL_DRESSING_PARAM_AUTO,
	HMC_WHEEL_DRESSING_PARAM_MANUAL,
	HMC_WHEEL_DRESSING_PARAM_EXIT,

	MAX_OP_MISC_PARAM_IDX
};

enum op_aging_param_idx {
	HMC_AGING_MODE_START,
	HMC_AGING_MODE_END,

	MAX_OP_AGING_PARAM_IDX
};

enum op_mode_chg_param_idx {
	HMC_MODE_NORMAL,
	HMC_MODE_AGING,

	MAX_OP_MODE_CHG_PARAM_IDX
};


// sensor id bit
#define HEX_SID_MAIN_CONTACT 0x01
#define HEX_SID_SBG_CONTACT 0x02
#define HEX_SID_CLAMP_SWITCH 0x04
#define HEX_SID_MAIN_MOTOR 0x08
#define HEX_SID_SBG_MOTOR 0x10
#define HEX_SID_DRILL_MOTOR 0x20
#define HEX_SID_PUMP1 0x40
#define HEX_SID_PUMP2 0x80

#define HEX_SID_PI_X 0x0100
#define HEX_SID_PI_Y 0x0200
#define HEX_SID_PI_R 0x0400
#define HEX_SID_PI_SBG 0x0800
#define HEX_SID_PI_DRILL_Y 0x1000
#define HEX_SID_PI_DRILL_T 0x2000
#define HEX_SID_HOLE 0x4000
#define HEX_SID_FENC_R 0x8000
#define HEX_SID_FENC_L 0x010000
#define HEX_SID_INV_FREQ 0x020000
#define HEX_SID_DRILL 0x040000

#define HEX_SID_R_FEELER_SWITCH 0x080000
#define HEX_SID_L_FEELER_SWITCH 0x100000
#define HEX_SID_AGING_COUNT 0x200000
#define HEX_SID_SBG_CURRENT 0x400000
#define HEX_SID_DOOR_CURRENT 0x800000
#define HEX_SID_DRILL_CURRENT 0x01000000
#define HEX_SID_CLAMP_CURRENT 0x02000000 // 20130617 add clamp current

#define HEX_SID_ALL 0x0fffffff 


typedef struct hex_sensor_status {
	int switch_flag; // HEX_SID_MAIN_CONTACT ~ HEX_SID_PUMP2 , 0 - off, 1 - on, HEX_SID_DRILL 추가 
	int x_pi; // HEX_SID_PI_X
	int y_pi; // HEX_SID_PI_Y
	int r_pi; // HEX_SID_PI_R
	int sbg_pi; // HEX_SID_PI_SBG
	int drill_y_pi; // HEX_SID_PI_DRILL_Y
	int drill_t_pi; // HEX_SID_PI_DRILL_T
	int window_hole_sensor; // HEX_SID_HOLE
	int r_feeler_encoder; // HEX_SID_FENC_R
	int l_feeler_encoder; // HEX_SID_FEND_L
	int inv_freq; // HEX_SID_INV_FREQ
	int aging_count; // HEX_SID_AGING_COUNT
	int sbg_current; // HEX_SID_SBG_CURRENT
	int door_current; // HEX_SID_DOOR_CURRENT
	int drill_current; // HEX_SID_DRILL_CURRENT

	int clamp_current; // HEX_SID_CLAMP_CURRENT // 20130617 add clamp current
} HEX_SENSOR_STAT;


// hmc_base.c
int send_hmc_packet(int uart, char * plabel, char *buf, int add_count);
int send_hex_motor_session(int uart, char *buf);

// hmc_error.c
int send_hmc_error_code(int uart, int error);
int send_hmc_error_msg(int uart, char *msg);

// hmc_ctl.c
int send_hmc_ctl(int uart, int cid, int op, int param);
int send_hmc_ctl_m(int uart, int cid, int op, int param);
int send_hmc_get_sensor_stat(int uart, int sid);

// hmc_ctl_m.c
int send_hmc_sensor_status(int uart, HEX_SENSOR_STAT *pss);
int send_hmc_sensor_status_str(int uart, char *ss);
int send_hmc_busy_status(int uart, int status);

// hmc_ctl_p.c
void print_HEX_SENSOR_STAT(HEX_SENSOR_STAT *p_stat);
int parse_hex_sensor_stat_str(char *str, HEX_SENSOR_STAT *p_stat);

// hmc_ack.c
int recv_hmc_ack(int uart, int time_out);

// hmc_start.c
int send_hmc_start_job(int uart, char *job_str, int process_option, int side);
int send_hmc_start_job_ext(int uart, char *job_str, int process_option, int side, char *param);

// hmc_wps.c
int send_hmc_work_progress(int uart, char *wps);


// hmc_init.c
int send_hmc_init(int uart, int emergency);
int recv_hmc_ver(int uart, char *ver_str, int size, int time_out);

// hmc_init_m.c
int send_hmc_ver(int uart, char *ver_str);
int recv_hmc_init_and_send_ver(int uart, char *ver_str, int *p_emergency);

// hmc_edging_param.c
int send_hmc_edging_param(int uart, char *job_no, struct epc_edging_param *param);
int send_hmc_retouch_param(int uart, char *job_no, struct epc_retouch_param *param);

// hmc_drill.c
int send_hmc_drill_data(int uart, char *job_no, int flag, struct epc_drill_data *p_drill, int max);

// hmc_wnd.c
int send_hmc_window(int uart, int stat);

// hmc_rcv.c
int recv_hex_calibration_data(int uart, char *buf, int size, int time_out);

// hmc_err_ans.c
int send_hmc_err_ans(int uart, int ans);

// hmc_err_req.c
int send_hmc_err_req(int uart, int err);

/// ui 로 부터 error 에 대한 answer code 를 받는다.
/// used in motor
/// \param uart uart 번호
/// \param p_ans (out) answer code
/// \param time_out 대기시간 (초), 음수 이면 반복 횟수 (-1 이면 1번만 검사, -5 이면 5번 검사)
/// \return 0 answer code 수신
/// \return -ERR_INVAL answer code 없음
/// \return -ERR_TIMEOUT;
static INLINE int recv_hmc_err_ans(int uart, int *p_ans, int time_out)
{
	return recv_packet_int_value(uart, PACKET_HMC_ERR_ANS, p_ans, time_out);
}



// hmc_list.c
int send_hmc_list(int uart, char *name, int type, void *list_p, int count, int width, int period_width);

// hmc_list_r.c
int parse_hmc_list(char *buf, char *name, void **p_list, int *p_count);


// 20110421 모터 전송 패킷 디버깅용 코드 
//#define _DUMP_HMC_PACKET_

void dump_hmc_packet(int onoff);
void reset_hmc_packet_buffer(void);
void print_hmc_packet_buffer(void);



#endif 
/********** end of file **********/
