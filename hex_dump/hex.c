/*!
  \file hex.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Mon Nov 07 15:09:15 KST 2011

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
	int fd;
	unsigned char buf[1024];
	int i;
	int ret;
	int total = 0;

	if ( argc < 2 ) { 
		fprintf(stderr, "usage : %s filename\n", argv[0]);
		return 1;
	}


	fd = open(argv[1], O_RDONLY);
	if ( fd < 0 ) {
		perror("open error ");
		return 2;
	}


	while ( ( ret = read(fd, buf, sizeof(buf))) > 0 ) {
		total += ret;
		printf("read %d bytes\n", ret);
		for ( i = 0 ; i < ret ; i++ ) {
			printf("0x%02x, ", buf[i]);

			if ( ( (i+1) % 8) == 0 ) {
				printf("\n");
			}
		}
		printf("\n");
	}
	close(fd);

	printf("total %d bytes\n", total);

	return 0;
}

