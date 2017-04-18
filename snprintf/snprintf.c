#include <stdio.h>

int main(void)
{
	int ret ;
	char buf[4];

	ret = snprintf(buf, sizeof(buf), "hello %.2f world !!!", 18.18);

	printf("ret = %d\n", ret);
	printf("[1234567890]\n");
	printf("[%s]\n", buf);

	return 0;
}

