/*!
  \file xor.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Nov 16 18:47:44 KST 2011

*/
#include <stdio.h>



/// tester main
int main(void)
{
	int a, b, c;

	a = 0x01 | 0x04;
	b = 0x01 | 0x08;

	c = a ^ b;

	printf("0x%x ^ 0x%x = 0x%x\n", a, b, c);
	return 0;
}
/********** end of file **********/
