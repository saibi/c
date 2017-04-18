/*!
 * \file comm_base.h
 * \brief
 *
 * 20070326 comm_common.h 에서 comm_base.h 로 이름 변경 (cpe gui old 통신 코드와 중복되는 파일이름이라서...)
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 월  3월 26 21:53:37 KST 2007
 *
*/
#ifndef _COMM_BASE_H_
#define _COMM_BASE_H_

#include "llist.h"

/// uart 수신 버퍼 크기 
#define COMM_UART_BUF_SIZE (128*1024) // 128KB, 보통 full frame 이 전송될때 약 25000bytes 정도가 전송된다.

#define COMM_TIMEOUT_DURATION 12 // 통신 타임아웃 12초 

// 통신 옵션 
#define COMM_OPTION_GEN_CRC 0x01 // 패킷 전송시 CRC 추가 
#define COMM_OPTION_CHECK_CRC 0x02 // 패킷 수신시 CRC 검사
#define COMM_OPTION_DUMP_SEND_PACKET 0x04 // 패킷 전송시 내용 dump
#define COMM_OPTION_DUMP_RECV_PACKET 0x08 // 패킷 수신시 내용 dump
#define COMM_OPTION_STRICT_CRC_CHECK 0x10 // FM 대로 CRC 검사 (COMM_OPTION_CHECK_CRC 가 정의된 상태에서만 동작한다)

// 패킷 수신을 위한 사용자 정의 uart flag
#define COMM_BUF_FLAG_PACKET_RECEIVED 0x1000
#define COMM_BUF_FLAG_ACK_RECEIVED 0x2000
#define COMM_BUF_FLAG_PACKET_START 0x4000
#define COMM_BUF_FLAG_BARCODE 0x8000 // barcode uart 일 경우 설정 
#define COMM_BUF_FLAG_INVALID_GS 0x010000 // invalid GS 상태 표시

struct comm_uart_handler_rec {
	int comm_buffer_flag;
	struct list_head received_packet_list;
	struct list_head used_packet_list; // 이미 처리한 패킷
	int comm_uart_buf_size;
	int (*packet_scan_function)(char *, int, char**);
	struct comm_packet *recent_packet;
	void * comm_time_loop_handler;

	// default timeout (단위: 초)
	int default_comm_timeout_second;

	// 통신 옵션
	int default_comm_option;

	// nak 응답시 재시도 횟수
	int default_comm_retry_count;
};



// 패킷 타입 검사를 위한 table 구조체
struct packet_type_strmap {
	char *str;
	int type;
};


// 패킷 구조체
struct comm_packet {
	int type; 
	int size;
	unsigned int time;
	void *extra; // 기타 부가 정보 저장용 필드 (메모리를 할당해서 쓰던지, int 용으로 쓰던지 상황에 따라 알아서 쓸것)
			// 20070402 extra 필드에 packet type scan 포인터 저장
	struct list_head list;

	char buf[ZERO_ARRAY_IDX]; // 이 필드는 memory 위치를 알기위한 
				// dummy 포인터이다.
				// salloc() 으로 메모리를 할당할때 
				// 버퍼 크기 까지 포함하도록 한다.
				//
				// sdt 2.5 에서 xx[0] 지원 안함
				// xx[1] 로 대체
};

extern struct comm_uart_handler_rec *comm_uart_data;

int init_comm_data(int max );
void set_packet_scanner(int uart, int (*func)(char *, int, char **) ) ;
void set_comm_uart_buf_size(int uart, int size);
int init_comm_uart_handler(int uart, int (*)(char *, int, char**) );
void free_comm_uart_handler(int uart);
void packet_receiver(int uart, char ch);
int get_current_packet_count(int uart);


#define GET_RECENT_PACKET(no) (comm_uart_data[no].recent_packet)

#define free_barcode_uart_handler(uart) free_comm_uart_handler(uart)



/// 패킷을 수신하기 시작 했는가?
#define IS_PACKET_START(no) (comm_uart_data[no].comm_buffer_flag & COMM_BUF_FLAG_PACKET_START)

/// 패킷을 전부 수신했는가?
#define IS_PACKET_RECEIVED(no) (comm_uart_data[no].comm_buffer_flag & COMM_BUF_FLAG_PACKET_RECEIVED)

/// ack 패킷을 수신했는가?
#define IS_ACK_RECEIVED(no) (comm_uart_data[no].comm_buffer_flag & COMM_BUF_FLAG_ACK_RECEIVED)

/// barcode uart 인가 ?
#define IS_BARCODE_UART(no) (comm_uart_data[no].comm_buffer_flag & COMM_BUF_FLAG_BARCODE)


/// flag 설정 
#define SET_COMM_BUFFER_FLAG(no, flag) comm_uart_data[no].comm_buffer_flag |= (flag)
#define SET_COMM_BUFFER_FLAG_VALUE(no, value) comm_uart_data[no].comm_buffer_flag = (value)
/// flag 해제
#define CLEAR_COMM_BUFFER_FLAG(no, flag) comm_uart_data[no].comm_buffer_flag &= (~(flag))



/// 통신 time loop handler 설정 
/// \param handler
static INLINE void set_comm_time_loop_handler(int uart, void *handler) 
{
	comm_uart_data[uart].comm_time_loop_handler = (void*)handler;
}

/// 통신 time loop handler 해제 
static INLINE void clear_comm_time_loop_handler(int uart)
{
	comm_uart_data[uart].comm_time_loop_handler = NULL;
}


/// time out loop handler 실행
/// \return 0 이면 loop 계속 진행 
/// \return 음수 loop 중단할 것 
static INLINE int RUN_COMM_TIME_LOOP_HANDLER(int uart) 
{
	if ( comm_uart_data[uart].comm_time_loop_handler ) { 
		return ((int (*)(void))comm_uart_data[uart].comm_time_loop_handler)();
	} 
	return 0;
}

/// 패킷 송/수신 시에 사용할 timeout 설정 (초단위)
/// 호출 횟수가 빈번하지 않아 함수로 처리함
/// \param val timeout
static INLINE void set_default_comm_timeout( int uart, int val ) 
{
	//ASSERT( val >= 0 );

	comm_uart_data[uart].default_comm_timeout_second = val;
}

/// 패킷 송/수신용 timeout 얻음
/// \return timeout
static INLINE int get_default_comm_timeout(int uart)
{
	return comm_uart_data[uart].default_comm_timeout_second;
}


/// 통신에러 발생시 (보통 ACK 대신에 NAK 으를 받았을 경우) 재시도 횟수 설정
/// \param uart
/// \param val 재시도 횟수
static INLINE void set_default_comm_retry_count( int uart, int val ) 
{
	//ASSERT( val >= 0 ) ;
	comm_uart_data[uart].default_comm_retry_count = val;
}

/// 통신 재시도 횟수 얻음
/// \param uart
/// \return retry_count
static INLINE int get_default_comm_retry_count(int uart)
{
	return comm_uart_data[uart].default_comm_retry_count;
}

/// 통신 옵션 설정 
/// \param uart
/// \param val 통신 옵션,  see comm_frame.h #define COMM_OPTION_xxxx 
static INLINE void set_default_comm_option ( int uart, int val )
{
	comm_uart_data[uart].default_comm_option = val;
}

/// 통신 옵션 얻음
/// \param uart
/// \return option
static INLINE int get_default_comm_option(int uart)
{
	return comm_uart_data[uart].default_comm_option;
}

/// 수신 패킷 리스트 head pointer 리턴 
/// \return list_head
static INLINE struct list_head * get_received_packet_list_head(int uart)
{
	return &comm_uart_data[uart].received_packet_list;
}

/// 통신 버퍼 플래그 얻음
/// \return flag
static INLINE int get_comm_buffer_flag(int uart)
{
	return comm_uart_data[uart].comm_buffer_flag;
}








// comm_build.c
void set_barcode_parsing_func(void *func);
struct comm_packet * make_packet(int uart, char *buf, int size, int type);
int parsing_comm_handler_buffer_and_make_packet(int uart, char *buf, int max);
void build_received_packet(int uart);
int get_request_type_str(char *packet_buf, char *buf);
int get_received_packet(int uart, char *request_type, char **buf, int *size);
void free_received_packet(int uart);
void free_used_packet(int uart);
struct comm_packet * search_received_packet(int uart, int type);
void delete_packet(struct comm_packet *p);


// comm_emul.c
int sec_add_comm_packet(int uart, char *buf, int size);
int sec_emulate_simple_comm_packet(int uart, char *packet_str);


// comm_parse.c
int get_packet_value(char *buf, char *value);
int get_job_str(char *packet_buf, char *buf);
int get_packet_status_code(char *packet_buf);

// comm_rcv.c
int recv_packet(int uart, int packet_type, int time_out);

// comm_pr_stat.c
void pr_comm_uart_status(int uart);

#endif
/********** end of file **********/
