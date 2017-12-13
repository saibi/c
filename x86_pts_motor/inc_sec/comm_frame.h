/*!
 * \file comm_frame.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 수  7월 05 12:12:49 KST 2006
 *
*/
#ifndef _COMM_FRAME_H_
#define _COMM_FRAME_H_

#include "iso16284_char_def.h"
#include "common_macro.h"



// iso16284 packet
// ascii 형식으로 프로토콜을 작성해 놓고 
// 주요 변수를 parameter 로 입력 받아
// binary 로 변환해서 보내도록 한다.
//
// 상수 끝에 _js 는 필요한 parameter 수 를 표시한다.


// data 를 보낼테니 준비해라
// 고급형 호환을 위해 <ACK> 가 추가됨 c8c8c8
#define PFMT_REQ_SEND_j 	\
	"<FS>" \
	"REQ=TRC<CR>" \
	"JOB=%s<CR>" \
	"<GS>"


// data 보낸다
// 별도 함수를 이용해 내용을 채운다. epc_frame_data_to_iso16284() 참조
#define PFMT_SEND_DATA_HEADER_rj \
	"<FS>" \
	"ANS=%s<CR>" \
	"JOB=%s<CR>" 

#define PFMT_SEND_DATA_FOOTER \
	"<GS>"


// 나한테 data 를 보내달라 
#define PFMT_REQ_RECEIVE \
	"<FS>" \
	"REQ=EDG<CR>" \
	"<GS>"

// 나한테 data 를 보내달라 (job no 지정) 
#define PFMT_REQ_RECEIVE_j \
	"<FS>" \
	"REQ=EDG<CR>" \
	"JOB=%s<CR>" \
	"<GS>"

///////////////////////////////////////


// data를 받을 수 있다.
#define PFMT_ANS_SEND_OK_rjs \
	"<FS>" \
	"ANS=%s<CR>" \
	"JOB=%s<CR>" \
	"STATUS=%d<CR>" \
	"<GS>"


// data 잘 받았다.
// 20070402 status 필드 추가함  
// PFMT_ANS_SEND_OK_rjs 와 동일하군 
// 만일을 대비해 일단 기존처럼  패킷을 구분해서 사용할 것
#define PFMT_RECEIVE_OK_rjs \
	"<FS>" \
	"ANS=%s<CR>" \
	"JOB=%s<CR>" \
	"STATUS=%d<CR>" \
	"<GS>"


// 20070319 CRC 는 통신 함수내에서 처리하도록 변경함 
//	"<RS>" 
//	"CRC=%s<CR>" 






/*
 
// protocol example 

tracer -> edger data 전송 

EDGER			TRACER
----------------------------------------------------------------
			REQ_SEND
ANS_SEND_OK
			SEND_DATA
RECEIVE_OK




edger -> tracer data 전송 

EDGER			TRACER
----------------------------------------------------------------
REQ_SEND
			ANS_SEND_OK
SEND_DATA
			RECEIVE_OK



edger <- tracer data 요청

EDGER			TRACER
----------------------------------------------------------------
REQ_RECEIVE
			SEND_DATA

*/



int send_frame_data(int uart, char *job_no, struct epc_frame_data *frame, int frame_count);
int recieve_pure_frame_data(int uart, char *job_no, struct epc_frame_data *frame, int frame_count);
int request_frame_data(int uart, char *job_no, struct epc_frame_data *frame, int frame_count);
int request_frame_data_ex(int uart, char *job_no, struct epc_frame_data *frame, int frame_count);
int receive_frame_data(int uart, char *job_no, struct epc_frame_data *frame, int frame_count);
int send_pure_frame_data(int uart, char * request_type, char *job_no, struct epc_frame_data *frame, int frame_count);

#define SFDF_OLD_CPE_4000 0x01
void set_send_frame_data_option(int flag);

#endif
/********** end of file **********/
