/*!
  \file shortc.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Tue Nov 01 09:12:07 KST 2011

*/
#include <stdio.h>
#include <stdlib.h>

unsigned short front[] = {
	512,
	509
};

unsigned short rear[] = {
	0,
	65535
};


int main(int argc, char *argv[])
{
	unsigned short a, b;
	int c = 0;
	float val;
	int i;

#define FEELER_SCALE (4*3.141592/2000)

	a = 1;
	b = 65535;

	printf("a=%d, b=%d\n", a, b);
	a=a-b;
	printf("a-b=%d\n", a);

	a = 30;
	b = 90;
	c = 100;

	printf("a-b = %d\n", a-b);
	printf("abs(a-b) = %d\n", abs(a-b));

	printf("a-c = %d\n", a-c);
	printf("abs(a-c) = %d\n", abs(a-c));

	for ( i = 0 ; i < 2 ; i ++ ) {
		val = (int)front[i] * FEELER_SCALE  * ( 1-0.5) + (int)rear[i] * FEELER_SCALE * (0.5);
		printf("[%d] %.2f\n", i, val);
	}



	return 0;
}
/********** end of file **********/
