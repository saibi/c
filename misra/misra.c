/*!
  \file misra.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Tue Mar 04 17:33:12 KST 2014

*/
#include <stdio.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

int main(void)
{
#if 0
	unsigned char port = 0x5aU;
	unsigned char result_8;
	unsigned short result_16;

	result_8 = (~port) >> 4;
	printf("%x\n", result_8);

	result_8 = ((unsigned char)(~port)) >> 4;
	printf("%x\n", result_8);

	result_16 = ((unsigned short)(~(unsigned short)port)) >> 4;
	printf("%x\n", result_16);
#endif 

	uint16_t a = 10U;
	uint16_t b = 65535U;
	uint32_t c = 0U;
	uint32_t d;

	d = (a + b) + c;
	printf("d = %d\n", d);

	d = a + (b + c);
	printf("d = %d\n", d);

	return 0;
}
/********** end of file **********/
