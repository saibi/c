#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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

	char bufout = 'D';
	char bufin;

	int c;
	while (1)
	{
		printf("reading\n");
		c = read(masterfd, &bufin, 1);
		printf("read %i bytes: %c\n", c, bufin);
		if (c == -1)
			break;

		sleep(1);
	}

	close(masterfd);

	return 0;
}
