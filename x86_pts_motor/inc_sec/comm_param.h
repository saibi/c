/*!
  \file comm_param.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  Last Modification date : Tue Oct 30 09:35:57     2007

*/
#ifndef _COMM_PARAM_H_
#define _COMM_PARAM_H_


#define PFMT_COMM_BRATE_i \
	"<FS>" \
	"BRATE=%d<CR>" \
	"<GS>"

#define RECORD_STR_PACKET_DUMP_LINE "DUMP" 
#define RECORD_STR_PACKET_CMD_LINE "CMD" 

// start 패킷에서는 name, size 추가
#define PFMT_BIN_START_si \
	"<FS>" \
	"BINSTART=%s,%d<CR>" \
	"<GS>"

// end packet 에서는 crc 추가
#define PFMT_BIN_END_i \
	"<FS>" \
	"BINEND=%d<CR>" \
	"<GS>"

// 살아있냐?
#define PFMT_ALIVE_s \
	"<FS>" \
	"ALIVE=%s<CR>" \
	"<GS>"



void send_line_packet_disable_crc(int onoff);
void send_line_packet(int uart, char *key_str, char *line);
int get_line_from_line_packet(char *packet_buf, char *line, int buf_size);

#define SEND_CMD_LINE(uart, line) send_line_packet(uart, RECORD_STR_PACKET_CMD_LINE, line)
#define SEND_DUMP_LINE(uart, line) send_line_packet(uart, RECORD_STR_PACKET_DUMP_LINE, line)


// comm_msg_dump.c
void add_msg_dump_uart(int uart);
void del_msg_dump_uart(int uart);
int get_msg_dump_uart_flag(void);
void msg_dump(char *msg);
void msg_dumpf(char *fmt, ...);

// comm_bin_send.c
int send_binary_file(int uart, char *name, char *file, int file_size);
	
// comm_bin_recv.c
#define SEC_COMM_BIN_LINE_SIZE 2000 // binary 를 한 번에 2000 bytes 씩 전송 
int recv_binary_file(int uart, char *file, int file_size);

// comm_brate.c
int send_comm_brate(int uart, int brate);
int setup_comm_brate(int uart, int brate, int timeout);


// comm_alive.c
int send_alive_packet(int uart, char *arg);
int recv_alive_packet(int uart, char *arg, int time_out);


#endif
/********** end of file **********/
