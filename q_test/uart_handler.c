/*!
  \file uart_handler.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : 월  2월 03 17:53:41 KST 2014

*/
#include <stdio.h>
#include <string.h>
#include <wrapper.h>
#include <uart_handler.h>


static CIRC_UART_BUFFER uart_buffer[MAX_UART_IDX];

/// enable uart handler
/// \param no uart channel
void enable_uart_handler(int no)
{
	if ( !uart_buffer[no].buf ) {
		printf("%s(%d) : error - uart buffer not set.\n", __FILE__, __LINE__);
		return;
	}
	
	switch (no ) {
		case 0:
			HW(NVIC_EnableIRQ(90));  // RxFIFOBufferEventHandler0 , UART001_Handle0
			break;

		case 1:
			HW(NVIC_EnableIRQ(89));  // RxFIFOBufferEventHandler1 , UART001_Handle1
			break;

		case 2:
			HW(NVIC_EnableIRQ(98));  // RxFIFOBufferEventHandler2 , UART001_Handle2  AA87 AB98
			break;
	}
	uart_buffer[no].flag |= UART_FLAG_ENABLE;
}


/// uart handler 를 중지 시킨다.
/// \param no uart 번호
void disable_uart_handler(int no)
{
	uart_buffer[no].flag &= ~(UART_FLAG_ENABLE);

	switch (no ) {
		case 0:
			HW(NVIC_DisableIRQ(90));  // RxFIFOBufferEventHandler0 , UART001_Handle0
			break;

		case 1:
			HW(NVIC_DisableIRQ(89));  // RxFIFOBufferEventHandler1 , UART001_Handle1
			break;

		case 2:
			HW(NVIC_DisableIRQ(98));  // RxFIFOBufferEventHandler2 , UART001_Handle2
			break;
	}

}

/// save data to uart buffer
/// \param uart
/// \param ch
void save_uart_character(int channel, char ch)
{
	// ASSERT : uart_buffer[channel].buf is ok 

	if ( ! (uart_buffer[channel].flag & UART_FLAG_ENABLE) ) {
		return;
	}

	if ( ! (uart_buffer[channel].flag & UART_FLAG_BUFFER_FULL) ) {
		uart_buffer[channel].buf[uart_buffer[channel].head] = ch;
		uart_buffer[channel].head++;
		if ( uart_buffer[channel].head >= uart_buffer[channel].size ) {
			uart_buffer[channel].head = 0;
		}
		if ( uart_buffer[channel].head == uart_buffer[channel].tail ) {
			uart_buffer[channel].flag |= UART_FLAG_BUFFER_FULL;
		}
	}
	if ( uart_buffer[channel].receiver) {
		((void (*)(int, char ))uart_buffer[channel].receiver)(channel, ch);
	}
}

// uart 0 isr
void RxFIFOBufferEventHandler0(void)
{
#if 0
	uint8_t ReadData;

	if(UART001_GetFlagStatus(&UART001_Handle0,UART001_FIFO_STD_RECV_BUF_FLAG) == UART001_SET)
	{

		ReadData = UART001_ReadData(UART001_Handle0);
		UART001_ClearFlag(&UART001_Handle0,UART001_FIFO_STD_RECV_BUF_FLAG);

		save_uart_character(0, ReadData);
	}
#endif 
}

void RxFIFOBufferEventHandler1(void)
{
#if 0
	uint8_t ReadData;
	if(UART001_GetFlagStatus(&UART001_Handle1,UART001_FIFO_STD_RECV_BUF_FLAG) == UART001_SET)
	{

		ReadData =  UART001_ReadData(UART001_Handle1);
		UART001_ClearFlag(&UART001_Handle1,UART001_FIFO_STD_RECV_BUF_FLAG);

		save_uart_character(1, ReadData);
	}
#endif 
}

void RxFIFOBufferEventHandler2(void)
{
#if 0
	uint8_t ReadData;
	if(UART001_GetFlagStatus(&UART001_Handle2,UART001_FIFO_STD_RECV_BUF_FLAG) == UART001_SET)
	{
		ReadData =  UART001_ReadData(UART001_Handle2);
		UART001_ClearFlag(&UART001_Handle2,UART001_FIFO_STD_RECV_BUF_FLAG);

		save_uart_character(2, ReadData);
	}
#endif 
}


/// set uart buffer
/// \param no uart channel
/// \param buf buffer pointer 
/// \param size buffer size
void set_uart_buffer(int no, char * buf, int size)
{
	uart_buffer[no].head = 0;
	uart_buffer[no].tail = 0;
	uart_buffer[no].flag = 0;
	uart_buffer[no].size = size;
	uart_buffer[no].buf = buf;
	uart_buffer[no].receiver = NULL;
}

/// character receiver 함수를 설정한다.
/// uart로 부터 문자를 받을 때 특별히 수행해야하는 기능이 있다면 이 receiver 를 사용하면 된다.
/// void receiver(char ch) 형태 함수이며 ch 는 현재 읽은 문자이다.
/// \param channel uart channel
/// \param receiver receiver 함수 (void*) 로 타입캐스팅해서 넘겨준다.
void set_uart_receiver(int no, void *receiver)
{
	uart_buffer[no].receiver = receiver;
}

/// uart handler 가 작동중인지 알아낸다.
/// \param no uart 번호
/// \return not_zero handler 작동중
/// \return 0 handler 중지 상태
int is_uart_handler_enabled(int no)
{
	return ( uart_buffer[no].flag & UART_FLAG_ENABLE);
}

/// uart buffer full 상태인가?
/// \param no uart channel
/// \return 1 yes
/// \return 0 no
int is_uart_handler_buffer_full(int no)
{
	if ( uart_buffer[no].flag & UART_FLAG_BUFFER_FULL ) {
		return 1;
	}
	return 0;
}

/// read uart buffer 
/// \param no uart channel
/// \param buf (out) 
/// \param buf_size 
/// \return size 
int read_uart_buffer(int no, char *buf, int buf_size)
{
	int after_len = 0;
	int before_len = 0;
	int remain_size = 0;

	int flag;
	int head;

	// TO-DO : disable handler
	flag = uart_buffer[no].flag;
	head = uart_buffer[no].head;
	// TO-DO : enable handler

	if ( flag & UART_FLAG_BUFFER_FULL ) {
		after_len = uart_buffer[no].size - uart_buffer[no].tail;
		before_len = uart_buffer[no].tail;
	} else {
		if ( uart_buffer[no].tail == head ) {
			// empty buffer
			return 0;
		}

		if ( uart_buffer[no].tail < head ) { 
			after_len = head - uart_buffer[no].tail; 
			before_len = 0;
		} else {
			after_len = uart_buffer[no].size - uart_buffer[no].tail; 
			before_len = head;
		}
	}

	if ( after_len > buf_size ) {
		memcpy(buf, &uart_buffer[no].buf[ uart_buffer[no].tail], buf_size);
		uart_buffer[no].tail += buf_size;
		goto out;
	} 

	memcpy(buf, &uart_buffer[no].buf[ uart_buffer[no].tail], after_len);
	remain_size = buf_size - after_len;

	if ( before_len > remain_size ) {
		memcpy(&buf[after_len], &uart_buffer[no].buf, remain_size);
		uart_buffer[no].tail = remain_size;
		goto out;
	}

	memcpy(&buf[after_len], &uart_buffer[no].buf, before_len);
	uart_buffer[no].tail = before_len;
	buf_size = after_len + before_len;

out:
	// TO-DO : disable handler
	uart_buffer[no].flag &= ~(UART_FLAG_BUFFER_FULL);
	// TO-DO : enable handler
	return buf_size;
}

/// return received size
/// \param no uart channel
/// \return size
int get_uart_buffer_recv_size(int no)
{
	int flag, head;

	// TO-DO : disable handler
	flag = uart_buffer[no].flag;
	head = uart_buffer[no].head;
	// TO-DO : enable handler

	if ( flag & UART_FLAG_BUFFER_FULL ) {
		return uart_buffer[no].size;
	}

	if ( uart_buffer[no].tail < head ) {
		return head - uart_buffer[no].tail;
	}

	return uart_buffer[no].size - uart_buffer[no].tail + head;
}

/// for backward compatibility
int get_uart_pos(int no)
{
	return get_uart_buffer_recv_size(no);
}

/// return buffer size
/// \param no uart channel
/// \return buffer_size
int get_uart_buffer_size(int no)
{
	return uart_buffer[no].size;
}

/// return buffer pointer
/// \param no uart channel
/// \return buffer
char * get_uart_buffer_pointer(int no)
{
	return uart_buffer[no].buf;
}

/// reset uart buffer
/// \param no uart channel
void reset_uart_buffer(int no)
{
	// TO-DO : disable handler

	uart_buffer[no].head = 0;
	uart_buffer[no].tail = 0;
	uart_buffer[no].flag = 0;

	// TO-DO : enable handler
}

/// dump uart handler data
/// \param no uart channel
void pr_uart_handler(int no)
{
	printf("uart buffer #%d\n", no);
	printf("buf = %p\n", uart_buffer[no].buf);
	printf("size = %d\n", uart_buffer[no].size);
	printf("head = %d\n", uart_buffer[no].head);
	printf("tail = %d\n", uart_buffer[no].tail);
	printf("flag = 0x%x\n", uart_buffer[no].flag);
	printf("receiver = %p\n", uart_buffer[no].receiver);
}

// for compatibility
void Uart_Rx_Irq_Enable(void)
{
	//enable_uart_handler(0);
	enable_uart_handler(1);
	enable_uart_handler(2);
}

void Uart_Rx_Irq_Disable(void)
{
	//disable_uart_handler(0);
	disable_uart_handler(1);
	disable_uart_handler(2);
}

/********** end of file **********/
