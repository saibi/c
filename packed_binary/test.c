/*!
  \file test.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Aug 10 11:02:53 KST 2011

*/
#include <escape.h>
#include <iso16284_pbf.h>
#include <stdio.h>
#include "data.h"

#define MAX_COUNT 400

INT_U8 packed_data[10240];
INT_U8 escaped_data[10240];
INT_U8 unescaped_data[10240];
INT_S16 unpacked_list[MAX_COUNT];


int main(int argc, char *argv[])
{
	int ret, ret2, i;

	printf("packed binary mode test\n");

#if 0
	printf("# org data -----------------------\n");
	for ( i = 0 ; i < MAX_COUNT; i++ ) {
		printf("[%d] %d\n", i, r_list[i]);
	}
	printf("\n");
#endif 


	ret = packit(r_list, packed_data, MAX_COUNT);
	printf("packit ret = %d\n", ret );

	ret2 = escape((char*)escaped_data, (char*)packed_data, ret);
	printf("escape ret2 = %d\n", ret2 );

	printf("escaped data ----------------------------\n");
	for ( i = 0 ; i < ret2; i++ ) {
		if ( escaped_data[i] < 32 || escaped_data[i] > 127 ) {
			printf("<%d>", escaped_data[i]);
		} else {
			printf("%c", escaped_data[i]);
		}
	}
	printf("\n");



	printf("# dest\n");

	ret = unescape((char *)unescaped_data, (char*)escaped_data, ret2);
	printf("unescape ret = %d\n", ret);

	printf("unescaped data ------------------------------\n");
	for ( i = 0 ; i < ret; i++ ) {
		if ( unescaped_data[i] != packed_data[i] ) { 
			printf("unescape error %d\n", i);
		}


		// print unescaped data
		if ( unescaped_data[i] < 32 || unescaped_data[i] > 127 ) {
			printf("<%d>", unescaped_data[i]);
		} else {
			printf("%c", unescaped_data[i]);
		}
	}
	printf("\n");

	ret2 = unpackit(unpacked_list, unescaped_data, MAX_COUNT);
	printf("unpackit ret2 = %d\n", ret2);

	printf("unpacked data ------------------------------\n");
	for ( i = 0 ; i < MAX_COUNT; i++ ) {
		if ( unpacked_list[i] < 0 ) { 
			printf("[%d] %d\n", i, (unsigned int)unpacked_list[i] & 0xffff);
		} else {
			printf("[%d] %d\n", i, unpacked_list[i]);
		}
		if ( unpacked_list[i] != r_list[i] ) {
			printf("error\n");
		}
	}

	return 0;
}
/********** end of file **********/

