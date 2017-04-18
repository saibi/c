/*!
  \file saibi_unpack.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Jul 27 13:43:41 KST 2011

*/

#include <stdio.h>

#define RD_16 0
#define RD_8 1
#define RD_4 2

#define L_AD 0
#define L_DI 1
#define L_DA 2
#define L_ID 3


static char *src_buf;

int read_value( int type )
{
}


#if 0

void unpack(int *dest, char *src, int src_size)
{
	int read_mode = RD_16;
	union {
		char ch[2];
		short i;
		signed char b;
	} word;
	int i;


	i = 0;

	while(1) {
		if ( read_mode == RD_16 ) {
			word.ch[0] = src[i++];
			word.ch[1] = src[i++];
		} else if ( read_mode == RD_8 ) {
			word.b = src[i++];
		} else {
		}


	}
}
#endif 




int main(int argc, char *argv[])
{
	union {
		struct {
			signed lo:4;
			signed hi:4;
		} nibble;
		char b;
	} byte;

	byte.b = 0x6b;

	printf("%x %d hi(%d %x), lo(%d %x)\n", byte.b, byte.b, byte.nibble.hi, byte.nibble.hi, byte.nibble.lo, byte.nibble.lo);

	return 0;
}

/********** end of file **********/
