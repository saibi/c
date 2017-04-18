#include <stdio.h>

#define A "A"

#if A == "A"
#define B 1
#else
#define B 2
#endif


int main(void)
{
	printf("%d\n", B);
	return 0;
}

