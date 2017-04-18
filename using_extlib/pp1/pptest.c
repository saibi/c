#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ssl_common.h>

int main(void)
{
	char buf[128] = { 0, };
	char param[128] = { 0, };
	int ret;

	printf("parse param test\n");
	ret = parse_param(param, "s", buf);
	printf("ret = %d\n", ret);
	return 0;
}

/********** end of file **********/
