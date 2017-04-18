#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	char buf[128] = "12ABCdef345";

	printf("%d\n", atoi(buf));
	return 0;
}

