/*!
  \file serial.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Dec 08 20:01:15 KST 2010

*/
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <serial.h>

static struct termios oldtio;
static int serial_fd;

/// baud rate string 을 timio 의 brate 상수로 변경 
/// \param str
/// \return brate
static int speed_str_to_brate(char *str)
{
	char *support_speed[] = {
		"1200",
		"2400",
		"4800",
		"9600",
		"19200",
		"38400",
		"57600",
		"115200",
		NULL
	};
	int brate_val[] = {
		B1200,
		B2400,
		B4800,
		B9600,
		B19200,
		B38400,
		B57600,
		B115200,
		0,
	};
	int i;

	for ( i = 0 ; support_speed[i] != NULL; i++) {
		if ( strcmp(str, support_speed[i]) == 0 ) {
			return brate_val[i];
		}
	}
	// default
	return B115200;
}

/// open serial port
/// \param port
/// \param baud
/// \return fd file descriptor on success
/// \return -1 error 
int open_serial_port(char *port, char *baud_str)
{
	struct termios newtio;

	serial_fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY );
	if ( serial_fd < 0 ) {
		printf("open_serial_port(%s, %s) ", port, baud_str);
		perror("open error");
		return -1;
	}

	tcgetattr(serial_fd, &oldtio); /* save current serial port settings */
	memset(&newtio, 0, sizeof(newtio)); /* clear struct for new port settings */

	newtio.c_cflag = speed_str_to_brate(baud_str) | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR | IGNBRK;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;

	newtio.c_cc[VTIME]    = 1;     /* inter-character timer unused */
	newtio.c_cc[VMIN]     = 32;     /* blocking read until xxx character arrives */

	/* 
	now clean the modem line and activate the settings for the port
	*/
	tcflush(serial_fd, TCOFLUSH);
	tcflush(serial_fd, TCIFLUSH);
	tcsetattr(serial_fd,TCSANOW, &newtio);

	return serial_fd;
}


/// 시리얼 포트 닫기
/// \return 0 success
/// \return -1 not opened
void close_serial_port(void)
{
	if ( serial_fd > 2 ) {
		tcsetattr(serial_fd, TCSANOW, &oldtio);
		close(serial_fd);
		serial_fd = 0;
	}
}
/********** end of file **********/
