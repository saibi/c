/*!
 * \file send_packet.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 화 8 12  대한민국 표준시 2008
 *
*/
#ifndef _SEND_PACKET_H_
#define _SEND_PACKET_H_

extern void (*send_packet)(int, char *, int);
extern void (*send_byte_packet)(int, int);

void redirect_send_packet(int uart, char *buf, int size);
void redirect_send_byte_packet(int uart, int ch);
void set_send_packet_redirect_mode(int onoff);

#endif
/********** end of file **********/
