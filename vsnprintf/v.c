#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>


static void test(char *fmt, ...)
{
	va_list ap;
	int len = 0;
	static char *p = NULL;
	static int buf_size = 0;

	va_start(ap, fmt);
	len = vsnprintf(p, buf_size, fmt, ap);
	va_end(ap);

	if ( len >= buf_size )
	{
		if ( p ) 
			free(p);

		p = (char*)malloc(len + 1);
		if ( p ) 
		{
			va_start(ap, fmt);
			len = vsnprintf(p, len + 1, fmt, ap);
			va_end(ap);

			buf_size = len + 1;

			printf("allocated, buf_size = %d\n", buf_size);
		}
		else 
		{
			p = NULL;
			buf_size = 0;

			printf("insufficient memory.\n");
		}
	}

	printf("len = %d\n", len);
	printf("[%s]\n", p);
}

int main(void)
{
	
	printf("vsnprintf test\n");

	test("test %d", 10);
	test("apple");
	test("hello %s !!!", "world");


	return 0;
}
