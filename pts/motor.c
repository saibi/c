#include <stdio.h>
#define _XOPEN_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define CHAR_FS 0x1c
#define CHAR_GS 0x1d
#define CHAR_CR 0x0d
#define CHAR_RS 0x1e

static void replace_buf(char *buf)
{
	char *p;

	while( (p = strchr(buf, CHAR_FS) ) )
		*p = ' ';

	while( (p = strchr(buf, CHAR_GS) ) )
		*p = ' ';

	while( (p = strchr(buf, CHAR_CR) ) )
		*p = ' ';

	while( (p = strchr(buf, CHAR_RS) ) )
		*p = ' ';
}

static void send_packet(char *contents)
{
}


int main(int argc, char *argv[])
{
	// get the master fd
	int masterfd = open("/dev/ptmx", O_RDWR | O_NOCTTY);
	if (masterfd < 0)
	{
		perror("getpt");
		exit(1);
	}
	// grant access to the slave
	if (grantpt(masterfd) < 0)
	{
		perror("grantpt");
		exit(1);
	}
	// unlock the slave
	if (unlockpt(masterfd) < 0)
	{
		perror("unlockpt");
		exit(1);
	}
	// get the path to the slave
	char slavepath[64];
	if (ptsname_r(masterfd, slavepath, sizeof(slavepath)) < 0)
	{
		perror("ptsname_r");
		exit(1);
	}

	printf("Using %s\n", slavepath);

	char buf[1024] = {0, };
	printf("reading\n");
	int c;

	while (1)
	{
		++no;
		c = read(masterfd, buf, sizeof(buf)-1);
		if ( c > 0 ) 
		{
			replace_buf(buf);
			printf("%s\n", buf);

			if ( strstr(buf, "req motorver") ) 
			{

			}

			memset(buf, 0, sizeof(buf));
		}

		sleep(1);
	}

	close(masterfd);

	return 0;
}

