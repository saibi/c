#include <stdio.h>

#define LOOP_COUNT 10000000

static short calc_short(void)
{
	int i;
	short result = 0;

	for ( i = 1 ; i <= LOOP_COUNT; ++i )
	{
		result += ( (i * i + i * 13 - 3 ) % 7) * 19 / (i % 17 + 1 ) ;
	}
	return result;
}

static int calc_int(void)
{
	int i;
	int result = 0;

	for ( i = 1 ; i <= LOOP_COUNT; ++i )
	{
		result += ( (i * i + i * 13 - 3 ) % 7) * 19 / (i % 17 + 1 ) ;
	}
	return result;
}

static long calc_long(void)
{
	int i;
	long result = 0;

	for ( i = 1 ; i <= LOOP_COUNT; ++i )
	{
		result += ( (i * i + i * 13 - 3 ) % 7) * 19 / (i % 17 + 1 ) ;
	}
	return result;
}

int main(void)
{
	unsigned long  result = 0;

	result = calc_short() + calc_int() + calc_long();
	printf("%ld\n", result);
	return 0;
}

