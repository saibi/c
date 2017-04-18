#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>

#define VERSION_STR "0.1"

struct termios oldtio;

/// baud rate string to Baud rate 
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

/// 환경설정에 따라 시리얼 포트 열기 
/// \param port
/// \param baud
/// \return fd file descriptor on success
/// \return -1 open error
static int open_serial_port(char *port, int baud)
{
	int fd;
	struct termios newtio;

	fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY );
	if ( fd < 0 ) {
		perror("open error");
		return -1;
	}
	//fcntl(fd, F_SETFL, FNDELAY);
	fcntl(fd, F_SETFL, 0);

	tcgetattr(fd, &oldtio); /* save current serial port settings */
	memset(&newtio, 0, sizeof(newtio)); /* clear struct for new port settings */
	//memcpy(&newtio, &oldtio, sizeof(newtio)); 

	newtio.c_cflag &= ~CSIZE;
	newtio.c_cflag &= ~PARENB;
	newtio.c_cflag &= ~CSTOPB;
	newtio.c_cflag &= ~CSIZE;
	newtio.c_cflag &= ~CRTSCTS;
	newtio.c_cflag |= (B115200 | CS8 | CLOCAL); 

	newtio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	newtio.c_iflag |= (IGNPAR | IGNBRK);
	newtio.c_oflag &= ~OPOST;

	newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused */
	newtio.c_cc[VMIN]     = 1;     /* blocking read until xxx character arrives */


	/* 
	now clean the modem line and activate the settings for the port
	*/
	tcflush(fd, TCOFLUSH);
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW, &newtio);

	return fd;
}


/// 시리얼 포트 닫기
/// \return 0 success
/// \return -1 not opened
static void close_serial_port(int fd)
{
	tcsetattr(fd, TCSANOW, &oldtio);
	close(fd);
}

/// checksum 계산 
/// \param buf 
/// \param size
/// \return checksum
static int calc_checksum(unsigned char *buf, int size)
{
	unsigned short checksum = 0;
	int i;

	for ( i = 0; i < size ; i++) {
		checksum += buf[i];
	}
	return checksum;
}

/// file 읽기 (GB 이상의 큰 파일 처리 못함)
/// \param fd file descriptor
/// \param buf (out) 파일 내용이 저장될 버퍼 (충분히 메모리 확보해야한다)
/// \param size
/// \return file size
/// \return 음수 에러 
static int read_file(int fd, unsigned char *buf, int size)
{
	int rd_idx = 0;
	int ret;

	while( rd_idx < size ) {
		ret = read(fd, &buf[rd_idx], size);
		if ( ret <= 0 ) {
			break;
		}
		rd_idx += ret;
		size -= ret;
	}
	if ( ret < 0 ) {
		return ret;
	}
	return rd_idx;
}



/// load & convert file
static int load_file(char *file, unsigned char **pbuf)
{
	int fd;
	struct stat sb;
	unsigned char *buf;
	unsigned int new_sz;
	unsigned short new_checksum;

	fd = open(file, O_RDONLY);
	if ( fd < 0 ) {
		perror("file open");
		return -1;
	}

	if ( fstat(fd, &sb) < 0 ) {
		perror("stat");
		close(fd);
		return -2;
	}
	new_sz = sb.st_size + 4 + 2;

	// 메모리 확보
	buf = (unsigned char *)malloc( new_sz + 16);
	if ( buf == NULL ) {
		perror("insufficient memory.\n");
		close(fd);
		return -3;
	}

	memcpy(buf, &new_sz, 4); // size copy

	if ( read_file(fd, &buf[4], sb.st_size) < 0 ) {
		perror("read error");
		free(buf);
		close(fd);
		return -4;
	}

	new_checksum = calc_checksum(&buf[4], sb.st_size);
	memcpy(&buf[new_sz-2], &new_checksum, 2);
	close(fd);

	if (pbuf) {
		*pbuf = buf;
	}
	return new_sz;
}

/// file 쓰기 (GB 이상의 큰 파일 처리 못함)
/// \param fd file descriptor
/// \param buf (in) 쓸 파일 내용
/// \param size
/// \return file size
/// \return 음수 에러 
static int write_data(int fd, unsigned char *buf, int size)
{
	int wr_idx = 0;
	int remain_size = size;
	int ret;

	while( wr_idx < size ) {
		ret = write(fd, &buf[wr_idx], remain_size);
		if ( ret < 0 ) {
			if (errno == EAGAIN ) {
				//perror("write_data error");
				//printf("%d sleep\n", errno);
				usleep(1000);
				//printf("wake\n");
				continue;
			} else {
				break;
			}
		}
		wr_idx += ret;
		printf("%d\n", wr_idx);
		remain_size -= ret;
	}
	printf("\n");
	if ( ret < 0 ) {
		return ret;
	}
	return wr_idx;
}


int main(int argc, char *argv[])
{
	int fd_serial;
	unsigned char *buf = NULL;
	int buf_size = 0;
	char dev_path[1024] = {0, };
	char filename[1024] = {0, };
	char baud_rate_str[128] = "115200";
	int ret;

	printf("Huvitz .bin file sender for MacOSX V%s\n", VERSION_STR);
	if ( argc < 3 ) {
		printf("usage : %s /dev/xxx filename\n", argv[0]);
		return 1;
	}
	strncpy(dev_path, argv[1], sizeof(dev_path)-1);
	strncpy(filename, argv[2], sizeof(filename)-1);

	fd_serial = open_serial_port(dev_path, speed_str_to_brate(baud_rate_str) );
	if ( fd_serial < 0 ) {
		return 2;
	}

	printf("port opened.\n");

	buf_size = load_file(filename, &buf);
	if ( buf_size < 0 ) {
		printf("file load failed.\n");
		return 3;
	}
	printf("%d bytes loaded.\n", buf_size);

	ret = write_data(fd_serial, buf, buf_size);
	if ( ret < 0 ) {
		perror("write error");
	} else {
		printf("%d bytes transferred.\n", ret);
	}

	close_serial_port(fd_serial);


	printf("end\n");
	return 0;
}
/********** end of file **********/
