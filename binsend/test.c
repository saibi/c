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


int main(int argc, char *argv[])
{
	int fd;
	struct termios newtio;
	int ret;
	char test[1024] = {0, };

	printf("serial port test\n");

	fd = open(argv[1], O_RDWR | O_NOCTTY | O_NDELAY );
	if ( fd < 0 ) {
		perror("open error");
		return -1;
	}
	fcntl(fd, F_SETFL, 0);

	tcgetattr(fd, &newtio); /* save current serial port settings */
	newtio.c_cflag = B115200| CS8 | CLOCAL;
	//newtio.c_lflag = 0;
	//newtio.c_iflag = IGNPAR ;
	tcsetattr(fd, TCSANOW, &newtio);

	ret = write(fd, "abckjlc8c8c8c8\r", 9);
	printf("ret = %d\n", ret);

	while(1) {
		ret = read(fd, test, 10);
		printf("ret = %d\n", ret);
		printf("[%s]\n", test);
		if ( test[0] == 'q' ) {
			break;
		}
	}




#if 0
	tcgetattr(fd, &newtio); /* save current serial port settings */
	//memset(&newtio, 0, sizeof(newtio)); /* clear struct for new port settings */
	newtio.c_cflag |= (B115200 | CS8 | CLOCAL); 
	newtio.c_iflag |= (IGNPAR | IGNBRK);
	tcsetattr(fd,TCSANOW, &newtio);


	printf("write.....\n");
	ret = write(fd, test, strlen(test));
	printf("ret = %d\n", ret);

	tcflush(fd, TCOFLUSH);
#endif 

	close(fd);

	return 0;
}
/********** end of file **********/
