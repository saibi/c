#include <stdio.h>

int main(void)
{

	char char_A = 'A';
	char char_B = 'B';

	const char * myPtr1 = &char_A;
	char * const myPtr2 = &char_A;
	const char * const myPtr3 = &char_A;

	*myPtr1 = char_B; // not allowed
	myPtr2 = &char_B; // not allowed

	return 0;
}
