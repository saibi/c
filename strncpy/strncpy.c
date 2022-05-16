#include <stdio.h>
#include <string.h>

int main(void)
{
	char buf1[4];
	char src[8] = {0, };
	char dest[9] = {0, };

	strncpy(buf1, "abcd", 4);

	printf("strncpy test, [3] = %d\n", buf1[3]);

	strncpy(src, "hello123", 8);
	printf("src [%s]\n", src);

	strncpy(src, "world", 5);
	printf("src [%s]\n", src);

	return 0;
}

