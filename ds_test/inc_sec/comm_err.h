/*!
 * \file comm_err.h
 * \brief
 *
 * 통신 error code 
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 월  6월 12 20:31:10 KST 2006
 *
*/
#ifndef _COMM_ERR_H_
#define _COMM_ERR_H_

#if 0
// org edger error from 고급형 코드

// Motor initialization
#define ERR_FEELER_IS_NOT_CENTER            101
#define ERR_INIT_X_SENSOR                   102                            
#define ERR_INIT_Y_SENSOR                   103                            
#define ERR_INIT_R_SENSOR                   104                            
#define ERR_INIT_FEELER_SENSOR              105                            
#define ERR_INIT_SBG_SENSOR                 106                            
#define ERR_FEELER_NOT_IN_POSITION 107  // 휠러가 빠진상태 (자동 복구 불가능)

// for hex
#define ERR_INIT_DRILL_T 108
#define ERR_INIT_DRILL_Y 109


// EZ motor error code
#define ERR_X 121  
#define	ERR_Y 122
#define ERR_R 123 
#define ERR_FEELER 124
#define ERR_CLAMP 125
#define ERR_AGING_ALL 126

// Motor Edging
#define ERR_EDGING_DATA_ABNORMAL            201
#define ERR_FEELER_DATA_ABNORMAL            202
#define ERR_MAIN_CONTACT                    203
#define ERR_SBG_CONTACT                     204
#define ERR_CLAMP_TIME_OUT                  205
#define ERR_GROOVE_MOTOR_CURRENT            206
#define ERR_WINDOW_OPEN	207
#define ERR_SBG_OVER_CURRENT 208 // err req 
#define ERR_SBG_ABNORMAL_ADC 209

// Motor dimensions/ UI safety check
#define ERR_FEELER_FAIL                     301
#define ERR_LENS_TOO_THICK                  302
#define ERR_GROOVE_IMPOSSIBLE               303
#define ERR_SB_IMPOSSIBLE                   304
#define ERR_LENS_ADAPTOR_INTERFERENCE       305                
#define ERR_FC_INTERFERENCE                 306
#define ERR_NO_SIZE_MARGIN_FOR_SB           307
#define ERR_COMM                            308
#define ERR_CLAMP_OPEN                      309
#define ERR_R_L_DUPLICATED                  310
#define ERR_REMAINED_SIDE                   311
#define ERR_NO_LENS			312
#define ERR_LENS_SMALL			313

// Excelon XD
#define ERR_L_FEELER_SW			401 // L_FEELER_SW ERROR
#define ERR_R_FEELER_SW 		402 // R_FEELER_SW ERROR
#define ERR_DRILL_Y_REMOVE_LENSE 	403 // INIT DRILL Y 에서 REMOVE LENSE
#define ERR_FEELER_CALIBRATION_TIP_V 	404 // FEELER CALIBRATION에서 FEELER TIP 교정 ERROR (수직방향)
#define ERR_FEELER_CALIBRATION_TIP_H 	405 // FEELER CALIBRATION에서 FEELER TIP 교정 ERROR (수평방향)
#define ERR_DRILL_CALCULATE_NCS 	406 // DRILL 가공 시에 CALCULATE NCS  ERROR
#define ERR_DRILL_Y_OVER_RANGE		407 // DRILL Y 가공 범위 벗어남 -> GUI에서 드릴 가공 영역을 지정해서 벗어날 수는 없으나 혹시라도..
#define ERR_DOOR_OVER_CURRENT		408 // DOOR OVER CURRENT -> 손 끼었을때..
#define ERR_INIT_L_FEELER		409
#define ERR_INIT_R_FEELER		410
#define ERR_FEELER_TIMEOUT		411 // for backward compatibility
#define ERR_L_FEELER_PUSH_TIMEOUT	411 
#define ERR_DRILL_OVER_CURRENT		412
#define ERR_LENS_DRILL_TOO_THICK	413
#define ERR_LENS_DRILL_TOO_THIN		414
#define ERR_CONTACT_FAILURE_DRILL_ZIG	415
#define ERR_ABNORMAL_CONTACT_DRILL_ZIG	416
#define ERR_DOOR_TIMEOUT		417
#define ERR_DISABLE_MOVE_DRILLT		418
#define ERR_NO_ZIG			419
#define ERR_DIVIDE_BY_ZERO		420
#define ERR_L_FEELER_TOO_TIGHT		421 // 휠러에 걸림이 있어 휠링 할 수 없음 
#define ERR_DRILL_WRAP 			422 // Drill Wrap Mode, 모터 일시 정지
#define ERR_R_FEELER_PUSH_TIMEOUT	423
#define ERR_L_FEELER_PULL_TIMEOUT	424
#define ERR_R_FEELER_PULL_TIMEOUT	425
#define ERR_R_FEELER_TOO_TIGHT		426
#define ERR_AC_SERVO_NOT_READY		427
#define ERR_NO_DRESSING_STICK		428
#define ERR_CONF_CRC			429


// GUI initialization
#define ERR_FFS_INVALID_HEADER		1001
#define ERR_FFS_MEM_ALLOC_FAILED	1002
#define ERR_EEPROM_MISSING		1003
#define ERR_EEPROM_INCORRECT_CRC	1004
#define ERR_EEPROM_INVALID_FORMAT	1005


// CPE MOTOR <-> GUI error answer code
#define ERR_ANS_STOP			0
#define ERR_ANS_CONTINUE		1

#define END_DRILL			501
#endif 

#endif
/*********** end of file **********/
