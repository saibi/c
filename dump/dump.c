/*!
  \file dump.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Tue Mar 13 12:31:35 KST 2012

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static void dump_file(char *path, int size)
{
	int fd;
	int ret;
	unsigned char buf[1001];
	int i;
	int sum = 0;

	fd = open(path, O_RDONLY);
	if ( fd < 0 ) {
		fprintf(stderr, "open error %s\n", path);
		return;
	}

	printf("char data[] = {\n");
	do {
		ret = read(fd, buf, sizeof(buf)-1);
		if ( ret > 0 ) {
			if ( (sum + ret) > size ) { 
				ret = size - sum;
			}
			for ( i = 0 ; i < ret ; i++ ) {
				printf("0x%02x, ", buf[i] );
				if ( (i + 1) % 10 == 0 ) {
					printf("\n");
				}
			}
			sum += ret;
		}
	} while (ret > 0 && sum < size );
	printf("\n};\n");
	close(fd);
}

int main(int argc, char *argv[])
{

	if ( argc < 2 ) {
		printf("%s [filename] [size]\n", argv[0]);
		return 1;
	}
	dump_file(argv[1], atoi(argv[2]));
	return 0;
}
/********** end of file **********/
