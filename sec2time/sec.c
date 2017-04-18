#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	int sec;

	if ( argc < 2 ) 
	{
		printf("%s [second]\n", argv[0]);
		return 1;
	}

	sec = atoi(argv[1]);

	printf("%02d%02d%02d\n", sec / 3600, (sec % 3600) / 60, sec % 60);

	return 0;
}
