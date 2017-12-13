/*!
  \file comm_barcode.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Mon Jul 12 16:42:27 KST 2010

*/
#ifndef _COMM_BARCODE_H_
#define _COMM_BARCODE_H_

#define BARCODE_UART_BUF_SIZE (512) // barcode 는 512 면 충분하다 

int init_barcode_uart_handler(int uart);
void barcode_packet_receiver(int uart, char ch);
int recv_barcode_string(int uart, char *buf, int buf_size);

#endif
/********** end of file **********/
