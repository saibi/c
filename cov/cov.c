#include <stdio.h>
#include <stdlib.h>

int check_even(int param);

int check_even(int param)
{
	int result;

	if ( param & 0x01 ) 
		result = 1;
	else 
		result = 0;

	return result;
}


int main(int argc, char *argv[])
{
	int ret;
	int val;

	if ( argc > 1 ) 
	{
		val = atoi(argv[1]);
		ret = check_even( val );

		printf("%d -> %d\n", val, ret);
	}
	return 0;
}


