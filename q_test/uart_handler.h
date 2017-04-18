/*!
  \file uart_handler.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : 월  2월 03 17:59:06 KST 2014

*/
#ifndef _UART_HANDLER_H_
#define _UART_HANDLER_H_

// circular uart handler buffer structure 
typedef struct circ_uart_buffer_t {
	volatile int head;
	volatile int tail;
	char *buf;
	int size;
	void *receiver;
	volatile int flag;
} CIRC_UART_BUFFER;

#define UART_FLAG_ENABLE 0x01 // handler 사용 
#define UART_FLAG_BUFFER_FULL 0x04 // 버퍼 꽉참 

void enable_uart_handler(int no);
void disable_uart_handler(int no);
void set_uart_buffer(int no, char * buf, int size);
void set_uart_receiver(int no, void *receiver);
int is_uart_handler_enabled(int no);
int is_uart_handler_buffer_full(int no);
char * get_uart_buffer_pointer(int no);
int get_uart_buffer_size(int no);	
void reset_uart_buffer(int no);

int read_uart_buffer(int no, char *buf, int buf_size);
void pr_uart_handler(int no);
int get_uart_buffer_recv_size(int no);
int get_uart_pos(int no);

void save_uart_character(int channel, char ch);

void Uart_Rx_Irq_Enable(void);
void Uart_Rx_Irq_Disable(void);

void RxFIFOBufferEventHandler0(void);
void RxFIFOBufferEventHandler1(void);
void RxFIFOBufferEventHandler2(void);

#endif
/********** end of file **********/
