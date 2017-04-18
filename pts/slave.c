#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd = open("/dev/pts/36", O_RDWR | O_NOCTTY);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}

	char bufout = 'A';
	char bufin;

	char rdbuf[1024] = {0, };
	int rd_size;

	int c;
	while (1)
	{
		if (bufout == 'A')
			bufout = 'B';
		else if (bufout == 'B')
			bufout = 'A';
		printf("writing %c\n", bufout);
		c = write(fd, &bufout, 1);
		if (c == -1)
			break;

		rd_size = read(fd, rdbuf, sizeof(rdbuf));
		if ( rd_size > 0 ) 
		{
			printf("READ %d bytes [%s]\n", rd_size, rdbuf);
			memset(rdbuf, 0, sizeof(rdbuf));
		}
		sleep(1);
	}

	close(fd);

	return 0;
}
