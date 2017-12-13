/*!
 * \file comm_edger.h
 * \brief
 *
 * cpe gui <-> motor 통신
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 수  7월 18 11:29:09 KST 2007
 *
*/
#ifndef _COMM_EDGER_H_
#define _COMM_EDGER_H_



// clamp 동작시켜라 (GUI -> Motor, Motor -> GUI 응답)
#define PFMT_CPE_MOTOR_CLAMP \
	"<FS>" \
	"C_CLAMP<CR>" \
	"<GS>"

// 가공중 에러 발생시 GUI 에 전달하여 사용자의 응답 요청
// int 형 에러 코드 전달해야함
#define PFMT_CPE_MOTOR_ERR_REQ_e \
	"<FS>" \
	"C_ERR_REQ=%d<CR>" \
	"<GS>"
	

// 가공중 에러 발생시 GUI 에서 motor 에 사용자 응답 전달
// parameter 로 int 형 answer 코드 전달해야함
#define PFMT_CPE_MOTOR_ERR_ANS_a \
	"<FS>" \
	"C_ERR_ANS=%d<CR>" \
	"<GS>"


// SW version 정보 전송 
#define PFMT_CPE_MOTOR_SWVER_s\
	"<FS>" \
	"SWVER=%s<CR>" \
	"<GS>"

// motor init.
#define PFMT_CPE_MOTOR_INIT \
	"<FS>" \
	"REQ=INI<CR>" \
	"<GS>"

// motor emergency init.
#define PFMT_CPE_MOTOR_EMERGENCY_INIT \
	"<FS>" \
	"EMER=ENI<CR>" \
	"<GS>"

// test mode 
#define PFMT_CPE_MOTOR_TEST_MODE_si \
	"<FS>" \
	"C_TEST_MODE=%s;%d<CR>" \
	"<GS>"

// answer test mode (used in motor)
#define PFMT_CPE_MOTOR_ANS_TEST_MODE_s \
	"<FS>" \
	"C_TEST_MODE=%s<CR>" \
	"<GS>"

// error
#define PFMT_CPE_MOTOR_ERROR_i \
	"<FS>" \
	"C_ERROR=%d<CR>" \
	"<GS>"

// progress mode 
#define PFMT_CPE_MOTOR_PROGRESS_MODE_i\
	"<FS>" \
	"C_PROGRESS_MODE=%d<CR>" \
	"<GS>"

// motor init confirm.
#define PFMT_CPE_MOTOR_INIT_CONFIRM_i \
	"<FS>" \
	"ANS=INI<CR>" \
	"STATUS=%d<CR>" \
	"<GS>"

// frame job
#define PFMT_CPE_MOTOR_FRAME_JOB_j \
	"<FS>" \
	"REQ=UPL<CR>" \
	"JOB=%s<CR>" \
	"<GS>"

// frame job confirm
#define PFMT_CPE_MOTOR_FRAME_JOB_CONFIRM_js \
	"<FS>" \
	"ANS=UPL<CR>" \
	"JOB=%s<CR>" \
	"STATUS=%d<CR>" \
	"<GS>"

// frame data confirm  (status 필드가 빠짐)
#define PFMT_CPE_MOTOR_FRAME_DATA_CONFIRM_j \
	"<FS>" \
	"ANS=UPL<CR>" \
	"JOB=%s<CR>" \
	"<GS>"

// process mode
#define PFMT_CPE_MOTOR_PROCESS_MODE_ii \
	"<FS>" \
	"C_PROCESSING_MODE=%d,%d<CR>" \
	"<GS>"


// C_CCLAMP_PRESSURE - CC 가 두개인것 보니 최초 개발시 오타난것 같다.
#define PFMT_CPE_MOTOR_CLAMP_PRESSURE_i \
	"<FS>" \
	"C_CCLAMP_PRESSURE=%d<CR>" \
	"<GS>"

#define PFMT_CPE_MOTOR_FRAME_SIZE_i \
	"<FS>" \
	"C_FRAME_SIZE=%d<CR>" \
	"<GS>"

#define PFMT_CPE_MOTOR_EDGING_START_ii \
	"<FS>" \
	"C_START=%d,%d<CR>" \
	"<GS>"

#define PFMT_CPE_MOTOR_CALIBRATION_START \
	"<FS>" \
	"C_CALIBRATE_START<CR>" \
	"<GS>"

#define PFMT_CPE_MOTOR_SIZE_CALIBRATION_i \
	"<FS>" \
	"C_CALIBRATE_SIZE=%d<CR>" \
	"<GS>"

#define PFMT_CPE_MOTOR_FEELER_CALIBRATION_i \
	"<FS>" \
	"C_CALIBRATE_FEELER=%d<CR>" \
	"<GS>"

#define PFMT_CPE_MOTOR_SBG_CALIBRATION_i \
	"<FS>" \
	"C_CALIBRATE_GROOVING=%d<CR>" \
	"<GS>"

#define PFMT_CPE_MOTOR_CALIBRATION_FINISH \
	"<FS>" \
	"C_CALIBRATE_FINISH<CR>" \
	"<GS>"

#define PFMT_CPE_MOTOR_AGING_ii \
	"<FS>" \
	"C_AGING=%d;%d<CR>" \
	"<GS>"

#define PFMT_CPE_MOTOR_AGING_COUNTER_i \
	"<FS>" \
	"C_AGING_COUNTER=%d<CR>" \
	"<GS>"

#define PFMT_CPE_MOTOR_RETOUCH_DATA_siii \
	"<FS>" \
	"ANS=TRC<CR>" \
	"DO=%s<CR>" \
	"POLISH=%d<CR>" \
	"GR_DEPTH=%d<CR>" \
	"LMATTYPE=%d<CR>" \
	"<GS>"

// test mode with sequence number
#define PFMT_CPE_MOTOR_SEQ_TEST_MODE_sii \
	"<FS>" \
	"C_SEQ_TEST_MODE=%s;%d;%d<CR>" \
	"<GS>"

// answer seq test mode (used in motor)
#define PFMT_CPE_MOTOR_ANS_SEQ_TEST_MODE_is \
	"<FS>" \
	"C_SEQ_TEST_MODE=%d;%s<CR>" \
	"<GS>"

// for TEST Mode : same as old comm library comm_control.h

/* running option : no op */
#define OPT_NO_OP "O_NO_OP"

/* running option : Clamp test */
#define OPT_CLAMP_CLOSE "O_CLAMP_C"
#define OPT_CLAMP_OPEN "O_CLAMP_O"

/* running option : Feeler test */
#define OPT_FEELER_ORIGIN "O_FEELER_ORG"
#define OPT_FEELER_DOWN "O_FEELER_DOWN"

/* running option : Grooving test */
#define OPT_SBG_ORIGIN "O_SBG_ORG"
#define OPT_SBG_DOWN "O_SBG_DOWN"
#define OPT_SBG_ROTATE "O_SBG_ROT"
#define OPT_SBG_STOP "O_SBG_STOP"

/* running option : Wheel test */
#define OPT_WHEEL_ORIGIN "O_WHEEL_ORG"
#define OPT_WHEEL_LOW "O_WHEEL_LOW"
#define OPT_WHEEL_HIGH "O_WHEEL_HIGH"

/* running option : X test */
#define OPT_X_ORIGIN "O_X_ORG"
#define OPT_X_MOVE "O_X_MOV"

/* running option : Y test */
#define OPT_Y_ORIGIN "O_Y_ORG"
#define OPT_Y_MOVE "O_Y_MOV"

/* running option : axis test */
#define OPT_AXIS_ORIGIN "O_AXIS_ORG"
#define OPT_AXIS_ROTATE "O_AXIS_ROT"
#define OPT_AXIS_STOP "O_AXIS_STOP"

/* running option : Pump test */
#define OPT_PUMP_1 "O_PUMP_1"
#define OPT_PUMP_2 "O_PUMP_2"
#define OPT_PUMP_STOP "O_PUMP_STOP"

/* parking */
#define OPT_PARKING "O_PARKING"

/* sensor id */
#define SID_LIMIT_SWITCH      0x01     /* 000000000001 : clmap test */
#define SID_PI_FEELER         0x02     /* 000000000010 : feeler test */
#define SID_PI_FEELER_CENTER  0x04     /* 000000000100 : feeler test */
#define SID_FEELER_ENCODER    0x08     /* 000000001000 : feeler test */
#define SID_PI_SBG            0x10    /* 000000010000 : grooving test */
#define SID_CONTACT_SBG       0x20    /* 000000100000 : grooving test */
#define SID_MOTOR_CURRENT     0x40    /* 000001000000 : grooving test */
#define SID_PI_X              0x80   /* 000010000000 : x test */
#define SID_PI_Y              0x0100   /* 000100000000 : y test */
#define SID_CONTACT           0x0200 /* 001000000000 : y test */
#define SID_PI_R              0x0400 /* 010000000000 : rotation test */
#define SID_WINDOW_SWITCH     0x0800 /* 100000000000 : window test */


// for calibartion type, same as old ue_conf.h
#define CALIBRATION_DATA_SET_SIZE 0
#define CALIBRATION_DATA_SET_FEELER 1
#define CALIBRATION_DATA_SET_SBG 2


// cpe motor <-> ui comm constants : same as old comm_control.h
enum ENUM_PROGRESS_STATUS { PS_NONE, PS_FEELING, PS_ROUGHING, PS_FINISHING, PS_POLISHING, PS_GROOVING, PS_SB, PS_END = 6, PS_STOP, PS_ERROR };
// roughing pl direction value
#define ROUGHING_PL_DIRECTION_NORMAL 0
#define ROUGHING_PL_DIRECTION_REVERSE 1
enum P_MODE_ENUM { P_MODE_AUTO_FRONT_PERCENT, P_MODE_AUTO_FRONT_DELTA, P_MODE_AUTO_REAR_DELTA, P_MODE_AUTO_BASE_CURVE, P_MODE_MANUAL, P_MODE_RIMLESS };
enum AGING_ACTION_ENUM { AAE_X, AAE_Y, AAE_ROTATION, AAE_CLAMP, AAE_SBG, AAE_FEELER, AAE_ALL, AAE_WHEEL };




#define JOB_NO_STR_SIZE 128


// edging data structure
struct edging_data_4_motor {
	char side_str[2]; // edging side string , "R" or "L"
	int frame_type; // frame type
	int etyp; // edging type
	int lmattype; // lens material
	int fragile; // fragile mode
	int polish; // polish option
	int safety_beveling; // sb option
	int frame_change; // frame change
	int circumference;
	int grooving_depth; // grooving depth
	int grooving_width; // grooving width
	int sb_front; // sb front amount
	int sb_rear_small; // sb rear small amount
	int sb_rear_large; // sb rear large amount
	int r_supplement;
	int record_format; // ascii diff
	int record_number; // right record number
	int record[MAX_RECORD_SIZE];
	int angle[MAX_RECORD_SIZE];
};



/* function prototypes */

// cm_clamp.c
int send_cpe_motor_clamp(int uart);

// cm_err_req.c
int send_cpe_motor_err_req(int uart, int err);

// cm_err_ans.c
int send_cpe_motor_err_ans(int uart, int ans);

// cm_swver.c
int send_cpe_motor_swver(int uart, char *ver_str);
int recv_cpe_motor_init_n_send_cpe_motor_swver(int uart, char *ver_str, int *p_emergency);

// cm_init.c
int send_cpe_motor_init(int uart);
int send_cpe_motor_emergency_init(int uart);
int send_cpe_motor_init_n_recv_cpe_motor_swver(int uart, int emergency_flag, int time_step, char *ver_str, int size);

// cm_test_mode.c
int send_cpe_motor_test_mode(int uart, char *opt_str, int sensor_list);
int send_cpe_motor_seq_test_mode(int uart, char *opt_str, int sensor_list, int seq);
int recv_cpe_motor_seq_test_mode(int uart, char *value_str, unsigned int *seq, int size,  int time_out);

// cm_sensor.c
int send_cpe_motor_sensor_status(int uart, int *sensor_status, int status_count);
int send_cpe_motor_seq_sensor_status(int uart, int *sensor_status, int status_count, int seq);

// cm_error.c
int send_cpe_motor_error(int uart, int error);

// cm_progress.c
int send_cpe_motor_process_mode(int uart, int process_mode, int value);

// comm_edger.c
int send_cpe_motor_progress_mode(int uart, int pm);
int send_cpe_motor_init_confirm(int uart, int status);
int recv_cpe_motor_status(int uart, int packet_type, int *p_status, int time_out);
int recv_cpe_motor_job_confirm_ex(int uart, int packet_type, char *job_str, int *p_status, int time_out);
int send_cpe_motor_job_confirm(int uart, char *job_str, int status);
int send_cpe_motor_frame_data_confirm(int uart, char *job_str);

int send_cpe_motor_clamp_pressure(int uart, int value);
int send_cpe_motor_frame_job(int uart, char *job_number_str);
int send_cpe_motor_frame_size(int uart, int value);
int send_cpe_motor_edging_start(int uart, int side, int processing_option);
int send_cpe_motor_calibration_start(int uart);
int send_cpe_motor_calibration_finish(int uart);
int send_cpe_motor_calibration_type(int uart, int type, int mode);
int send_cpe_motor_aging(int uart, int action, int counter);
int send_cpe_motor_aging_counter(int uart, int counter);
int send_cpe_motor_retouch_data(int uart, char *do_type, int grooving_depth, int polish, int lmattype);
int send_cpe_motor_frame_data(int uart, char *job_number, char *do_type, int frame_type, int radii_format, char *radius_mode, char *trace_type, int z_format, char *z_mode, char *z_trace_type, int *left_radii, int *right_radii, int *left_z, int *right_z, int *left_angle, int *right_angle, int *left_zangle, int *right_zangle, int num_left_radii, int num_right_radii, int num_left_z, int num_right_z, int etype, int lmatttype, int fragile, int polish, int sb, int fc, int l_circumference, int r_circumference, int grooving_depth, int grooving_width, int sfb_forward_width, int sfb_rear_small_width, int sfb_rear_large_width);

int parse_trcfmt(char *fmt, int *record_fmt, int *record_number, char *radius_mode, char *record_side, char *trace_type);
int parsing_ascii_diff_record(char *line, int line_size, int type, int rev, int *list, int max);
int iso16284_to_edging_data(char *buf, struct edging_data_4_motor *param);
int iso16284_to_retouch_data(char *buf, struct edging_data_4_motor *param);


/// init confirm status 값을 받는다.
/// used in GUI
/// \param uart uart 번호
/// \param p_status (out) status code 
/// \param time_out 대기시간 (초), 음수 이면 반복 횟수 (-1 이면 1번만 검사, -5 이면 5번 검사)
/// \return 0 수신 ok
/// \return -ERR_INVAL 
/// \return -ERR_TIMEOUT;
static INLINE int recv_cpe_motor_init_confirm(int uart, int *p_status, int time_out)
{
	return recv_cpe_motor_status(uart, PACKET_CPE_MOTOR_INIT_CONFIRM, p_status, time_out);
}


/// SW version 정보를 받음
/// used in gui
/// \param uart
/// \param ver_str (out) 전송받은 version string
/// \param size ver_str size
/// \param time_out 대기시간 (초), 음수 이면 반복 횟수 (-1 이면 1번만 검사, -5 이면 5번 검사)
/// \return 0 version string 수신
/// \return -ERR_INVAL version string 없음
/// \return -ERR_TIMEOUT;
static INLINE int recv_cpe_motor_swver(int uart, char *ver_str, int size, int time_out)
{
	return recv_packet_value_string(uart, PACKET_CPE_MOTOR_SWVER, ver_str, size, time_out);
}

/// test mode 결과 string 을 받는다.
/// used in GUI
/// \param uart uart 번호
/// \param value_str (out) test mode string 
/// \param size value_str size
/// \param time_out 대기시간 (초), 음수 이면 반복 횟수 (-1 이면 1번만 검사, -5 이면 5번 검사)
/// \return 0 수신 ok
/// \return -ERR_INVAL 
/// \return -ERR_TIMEOUT;
static INLINE int recv_cpe_motor_test_mode(int uart, char *value_str, int size,  int time_out)
{
	return recv_packet_value_string(uart, PACKET_CPE_MOTOR_TEST_MODE, value_str, size, time_out);
}



/// ui 로 부터 error 에 대한 answer code 를 받는다.
/// used in motor
/// \param uart uart 번호
/// \param p_ans (out) answer code
/// \param time_out 대기시간 (초), 음수 이면 반복 횟수 (-1 이면 1번만 검사, -5 이면 5번 검사)
/// \return 0 answer code 수신
/// \return -ERR_INVAL answer code 없음
/// \return -ERR_TIMEOUT;
static INLINE int recv_cpe_motor_err_ans(int uart, int *p_ans, int time_out)
{
	return recv_packet_int_value(uart, PACKET_CPE_MOTOR_ERR_ANS, p_ans, time_out);
}


/// packet 을 수신한다.
/// \param uart uart 번호
/// \param packet_type 수신하려고 하는 packet type
/// \param time_out 대기시간 (초), 음수 이면 반복 횟수 (-1 이면 1번만 검사, -5 이면 5번 검사)
/// \return 0 packet 수신
/// \return -ERR_TIMEOUT
static INLINE int recv_cpe_motor_packet(int uart, int packet_type, int time_out)
{
	return recv_packet(uart, packet_type, time_out);
}

#define recv_cpe_motor_job_confirm(uart, job_str, p_status, time_out) recv_cpe_motor_job_confirm_ex(uart, PACKET_CPE_MOTOR_FRAME_JOB_CONFIRM, job_str, p_status, time_out)


#endif
/********** end of file **********/

