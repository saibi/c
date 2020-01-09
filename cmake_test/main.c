#include <stdio.h>
#include "foo.h"
#include "bar.h"


int main(void)
{
	printf("I am main.\n");

	foo();
	bar();

	return 0;
}
