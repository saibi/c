/*!
  \file main.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : 2014/04/09 14:45:55 (KST)

*/
#include <stdio.h>

int sum(int, int);
int sub(int, int);

int main(void)
{
	printf("obj linking size test\n");

	printf("%d, %d\n", sum(1, 1), sub(1, 1));
	//printf("%d\n", sum(1, 1));

	return 0;
}
