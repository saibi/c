#include <stdio.h>
#define _XOPEN_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#include "support.h"

int grantpt(int fd);
int unlockpt(int fd);
int ptsname_r(int fd, char *buf, size_t buflen);

#define DP(fd, msg) do { printf(msg); send_msg(fd, msg); } while(0)
#define DPR(fd, rot) do { char tmp_buf[128]; sprintf(tmp_buf, "rotation = %d\n", rot); printf("%s", tmp_buf); send_msg(fd, tmp_buf ); } while(0)

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
	int read_size;


	printf("reading\n");
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		read_size = read(masterfd, buf, sizeof(buf)-1);
		if ( read_size > 0 ) 
		{
			pr_packet(buf);

			if ( strstr(buf, "req motorver") ) 
			{
				send_cmd(masterfd, "motorver 10.8");
			}
			else if ( strstr(buf, "start") && strstr(buf, "normal") )
			{

				DP(masterfd, "EDGING START\n");

				send_cmd(masterfd, "wps job start");
				send_cmd(masterfd, "wps edging start");

				DP(masterfd, "start feeling\n");

				send_cmd(masterfd, "wps feeling start");

				time_t start;
				int i = 0;
				start = time(NULL);
				while ( difftime( time(NULL), start)  < 60.0 ) 
				{
					send_wps_rot(masterfd, ++i);
					DPR(masterfd, i);
				}

				send_cmd(masterfd, "wps feeling end");
				DP(masterfd, "end feeling\n");

				sleep(1);

				DP(masterfd, "start roughing\n");
				send_cmd(masterfd, "wps roughing start");

				i = 0;
				start = time(NULL);
				while ( difftime( time(NULL), start)  < 60.0 * 10.0 ) 
				{
					send_wps_rot(masterfd, ++i);
					DPR(masterfd, i);
				}

				send_cmd(masterfd, "wps roughing end");
				DP(masterfd, "end roughing\n");

				sleep(1);

				DP(masterfd, "start finishing\n");
				send_cmd(masterfd, "wps finishing start");
				i = 0;
				start = time(NULL);
				while ( difftime( time(NULL), start)  < 60.0 * 5.0) 
				{
					send_wps_rot(masterfd, ++i);
					DPR(masterfd, i);
				}
				send_cmd(masterfd, "wps finishing end");
				DP(masterfd, "end finishing\n");

				sleep(1);
				send_cmd(masterfd, "wps edging end");
				send_cmd(masterfd, "wps job end");
				DP(masterfd, "EDGING END\n");
			}

		}
	}
	close(masterfd);

	return 0;
}

