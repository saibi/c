#include <stdio.h>
#include <string.h>

int main(void)
{
	char buf[8] = {0, };

	strncpy(buf, "helloworld", sizeof(buf));

	if ( strncmp(buf, "hello", 5) == 0 )
	{
		printf("hello 5 ok\n");
	}
	else 
	{
		printf("5 diff\n");
	}

	if ( strncmp(buf, "hello", 6) == 0 )
	{
		printf("hello 6 ok\n");
	}
	else 
	{
		printf("6 diff\n");
	}

	memset(buf, 0, sizeof(buf));
	strncpy(buf, "hello", sizeof(buf));

	if ( strncmp(buf, "hello", 5) == 0 )
	{
		printf("hello\\0 5 ok\n");
	}
	else 
	{
		printf("5 diff\n");
	}

	if ( strncmp(buf, "hello", 6) == 0 )
	{
		printf("hello\\0 6 ok\n");
	}
	else 
	{
		printf("6 diff\n");
	}

	return 0;
}
