#include <stdio.h>

int main(void)
{
	char buf[4];
	int ret ;
	char buf_clean[4] = { 0, };

	ret = snprintf(buf, sizeof(buf), "hello %.2f world !!!", 18.18);
	printf("buf ret = %d\n", ret);

	ret = snprintf(buf_clean, sizeof(buf_clean), "hello %.2f world !!!", 18.18);
	printf("buf_clean ret = %d\n", ret);

	printf("[1234567890]\n");
	printf("[%s] buf\n", buf);
	printf("[%s] buf_clean\n", buf_clean);

	return 0;
}

