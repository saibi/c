/*!
 * \file sec_common.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 화 5 13  Korea Standard Time 2008
 *
*/
#ifndef _SEC_COMMON_H_
#define _SEC_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


#ifdef _saibi_edger_comm_library_
//
// 라이브러이에만 적용되는 macro 
//
#include <external_func_proto.h>
#include <ssl_common.h>

#define _PACKET_CRC_ // 모든 packet 에 CRC 포함 
#define _DUMP_SEND_PACKET_ // packet 보낼때 dump 기능 추가 (해당 option 이 켜져야만 된다)
#define _DUMP_RCV_PACKET_
//#define _DUMP_CPE_MOTOR_COMM_PARAM_ // old cpe gui<->motor 통신 paramter 내용 확인하려면 



#define DCODE_CRC(x) // crc check debugging 
#define DCODE_PACKET( x ) // frame data 송/수신 디버깅 OFF
#define DCODE_PARSE(x) // packet parsing debugging
#define DCODE_EPC_TEXT(x) 
#define DCODE_BLD(x) // packet builder debugging 

#include "comm_packet_wrapper.h"

#endif 

#include <sec_ver.h>

// packet list
#include <sec_packet_type.h>

// error code
#include <comm_err.h>

// EPC
#include <epc.h>
#include <epc_type_def.h>
#include <epc_convert.h>
#include <epc_frame_data.h>
#include <epc_ascii_diff.h>
#include <epc_drill.h>
#include <epc_edging_param.h>
#include <epc_comm_frame.h>
#include <epc_comm_sub.h>
#include <epc_alloc_comm_frame.h>
#include <pr_epc_comm_frame.h>
#include <pr_drill_data.h>
#include <epc_text.h>
#include <epc_new_comm.h>
#include <epc_support.h>

// cpe-4000 iso16284 old header 
#include <iso16284_char_def.h>
#include <iso16284_record_label_def.h>

// vca dcs
#include <iso16284_record.h>
#include <iso16284_pbf.h>
#include <dcs.h>

// comm
#include <iso16284_common.h>
#include <send_packet.h>
#include <comm_base.h>
#include <comm_barcode.h>
#include <comm_packet.h>
#include <comm_param.h>
#include <comm_frame_opt.h>
#include <comm_edger_common.h>
#include <ez_sync.h>
#include <default_packet_scanner.h>
#include <comm_frame.h>
#include <comm_frame_drill.h>

// cm
#include <comm_edger.h>
#include <comm_motor_conf.h>


// hmc
#include <hmc_base.h>

#endif
/********** end of file **********/
