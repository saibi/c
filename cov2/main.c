#include <stdio.h>
#include <stdlib.h>


int even_odd(int param);

int main(int argc, char *argv[])
{
	if ( argc > 1 )
		even_odd(atoi(argv[1]));

	return 0;
}

