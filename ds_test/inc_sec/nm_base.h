/*!
  \file nm_base.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : 월  6 07 13:48:40 KST 2010

*/
#ifndef _NM_BASE_H_
#define _NM_BASE_H_


// enum sec_packet_type_idx 중복 되지 않도록 해야 한다. 
enum nm_packet_type_idx {
	PACKET_NM_CMD = 5001, 
	PACKET_NM_FILE, 
	PACKET_NM_FILE_CRC,  // not implemented
	PACKET_NM_BIG_FILE_START, 
	PACKET_NM_BIG_FILE_FRAG, 
	PACKET_NM_BIG_FILE_END, 
	PACKET_NM_MSG, 
	PACKET_NM_REQ, 
	PACKET_NM_ANS, 
	PACKET_NM_BUSY, 

	PACKET_NM_END
};

#define MAX_NM_PACKET_SIZE 20480

#define PL_NM_CMD "nmcm"

#define PL_NM_FILE "nmfi"
#define PL_NM_FILE_CRC "nmfc"

#define PL_NM_BF_START "nmbs"
#define PL_NM_BF_FRAG "nmbf"
#define PL_NM_BF_END "nmbe"

#define PL_NM_MSG "nmms"
#define PL_NM_REQ "nmrq"
#define PL_NM_ANS "nman"
#define PL_NM_BUSY "nmby"


// nm_base.c
unsigned int nm_get_seq(void);
void nm_set_busy_flag(int uart, int flag);
void nm_reset_seq(void);
int nm_send_busy(int uart, int flag);
int nm_send_cmd(int uart, char *cmd);
int nm_send_req(int uart, char *msg);
int nm_send_ans(int uart, char *msg, unsigned int req_seq);
int nm_send_msg(int uart, char *msg);
int nm_send_file(int uart, char *filename, char *buf, int size);
int nm_is_uart_busy(int uart);
void nm_set_big_file_fragment_size(int size);
int nm_get_big_file_fragment_size(void);

int convert_bin_to_nm_str(char *src, int src_size, char *dest);
int convert_nm_str_to_bin(char *src, int src_size, char *dest);



// nm_parse.c
int nm_get_packet_seq(char *packet, int packet_size, unsigned int *pseq);
int nm_get_ans_packet_str(char *packet, int packet_size, unsigned int *p_ansseq, char *buf, int buf_size);
int nm_get_packet_str(char *packet, int packet_size, char *buf, int buf_size);
int nm_handle_busy_flag(int uart, char *packet, int packet_size);
// for backward compatibility
#define nm_check_packet_crc(packet, packet_size) check_packet_buffer_crc(packet, packet_size)



// nm_rcv_file.c
int nm_handle_big_file(int opt, char *packet, int packet_size);
#define NM_BIG_FILE_START 0
#define NM_BIG_FILE_ADD 1 
#define NM_BIG_FILE_END 2 
int nm_get_big_file(char *filename, int *file_size, char **p_buf);
int nm_get_small_file(char *packet, int packet_size, char *filename, int *file_size, char **p_buf);

#endif
/********** end of file **********/
