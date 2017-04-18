/*!
  \file main.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Dec 08 19:50:10 KST 2010

*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <checksum.h>
#include <file.h>
#include <cmdarg.h>

/*
   ./bintr -p /dev/ttyUSB0 file
*/

/// bhc 형식으로 변환 (buf 은 read_bin_file() 로 읽어들여야 한다) 
static unsigned char * make_bhc_buf(unsigned char *buf, int size)
{
	int new_size = size + 4 + 2;
	unsigned short chk;
	unsigned char *p;

	chk = calc_checksum(buf, size);
	p = (unsigned char*)(buf - 4);
	memcpy(p, (char*)&new_size, 4);
	memcpy(&buf[size], &chk, 2);
	printf("DEBUG size %d , new size %d, checksum = %d\n", size, new_size, chk);
	return p;
}


int main(int argc, char *argv[])
{
	unsigned char *buf, *bhc_buf;;
	int ret;

	if ( proc_cmd_options(argc, argv) < 0 ) {
		exit(1);
	}

	ret = read_bin_file(bin_file_path, &buf);
	if ( ret < 0 ) {
		exit(2);
	}
	bhc_buf = make_bhc_buf(buf, ret);


	exit(0);
}
/********** end of file **********/


