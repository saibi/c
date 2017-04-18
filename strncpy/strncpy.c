#include <stdio.h>
#include <string.h>

int main(void)
{
	char buf1[4];


	strncpy(buf1, "abcd", 4);

	printf("strncpy test, [3] = %d\n", buf1[3]);

	return 0;
}

