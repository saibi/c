#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	FILE * fp;
	char line[128] = { 0, };
	unsigned int count = 0;

	fprintf(stderr, "fflush test\n");

	if ( argc < 2 ) 
	{
		fprintf(stderr, "usage : %s path\n", argv[0]);
		return 1;
	}


	fp = fopen(argv[1], "a");
	if ( fp == NULL )
	{
		fprintf(stderr, "fopen error %s\n", argv[1]);
		return 2;
	}

	while(1)
	{
		sprintf(line, "#%d 1234567890123456789012345678901234567890123456789012345678901234567890\n", count++);
		fputs(line, fp);
		fflush(fp);
		sleep(0.01);
	}

	fclose(fp);
	fprintf(stderr, "fflush end \n");
	return 0;
}
/********** end of file **********/
