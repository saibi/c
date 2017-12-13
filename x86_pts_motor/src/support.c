#include "support.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <iso16284_char_def.h>
#include <crc.h>
#include <iso16284_common.h>


static int add_crc_to_packet(char *buf, int size)
{
	char *crc_cal_start, *crc_cal_end;
	unsigned int crc;

	if (memchr(buf, CHAR_RS, size ) ) 
	{
		fprintf(stderr, "error : CHAR_RS exists\n");
		return -1;
	}

	if ( (crc_cal_start = (char*)memchr(buf, CHAR_FS, size)) == NULL ) 
	{
		fprintf(stderr, "error : CHAR_FS not found\n");
		return -1;
	}
	
	if ( (crc_cal_end = (char*)memchr(buf, CHAR_GS, size)) == NULL ) 
	{
		fprintf(stderr, "error : CHAR_GS not found\n");
		return -1;
	}

	crc_cal_start++; // <FS>는 포함하지않는다. 
	*crc_cal_end = CHAR_RS; // <GS> -> <RS> 

	crc = ccit_crc( 0, (unsigned char *)crc_cal_start, (int)crc_cal_end - (int)crc_cal_start +1);

	crc_cal_end++;

	sprintf(crc_cal_end, "CRC=%u%c%c", crc, CHAR_CR, CHAR_GS);

	return size + strlen(crc_cal_end);
}

static int make_nm_packet(char *buf, int buf_size, const char *label, const char *contents)
{
	static int seq = 0;
	int ret;

	ret = snprintf(buf, buf_size, "%c%s=%d;%s%c%c", CHAR_FS, label, seq++, contents, CHAR_CR, CHAR_GS);

	// too small buffer
	if ( ret + 12 >= buf_size )
	{
		fprintf(stderr, "error : too small buffer\n");
		return -1;
	}

	return add_crc_to_packet(buf, strlen(buf));
}

int make_nm_cmd_packet(char *buf, int buf_size, const char *contents)
{
	return make_nm_packet(buf, buf_size, "nmcm", contents);
}

int make_nm_msg_packet(char *buf, int buf_size, const char *contents)
{
	return make_nm_packet(buf, buf_size, "nmms", contents);
}

void pr_packet(char *buf)
{
	char * ptr = buf;
	int reserved = 0;
	int i;

	for ( ; *ptr ; ptr++ ) {
		for ( i = 0 ; iso16284_string_table[i].code >= 0; i++) {
			if ( iso16284_string_table[i].code == *ptr ) {
				printf("%s", iso16284_string_table[i].str);
				if ( *ptr != CHAR_ESC ) {
					printf("\n");
				}
				reserved = 1;
				break;
			}
		}
		if ( !reserved )  {
			if ( (*ptr < ' ') || (*ptr >= 127) ) {
				printf("<%02X>", (unsigned char)*ptr);
			} else {
				printf("%c", *ptr);
			}
		}
		reserved = 0;
	}
}

static char tmp_buf[4096];

int send_cmd(int fd, const char * cmd)
{
	int size;

	size = make_nm_cmd_packet(tmp_buf, sizeof(tmp_buf), cmd);

	if ( size <= 0 ) 
		return -1;

	return write(fd, tmp_buf, size);
}

int send_wps_rot(int fd, int count)
{
	char buf[128];

	snprintf(buf, sizeof(buf), "wps rot %d", count);

	return send_cmd(fd, buf);
}

int send_msg(int fd, const char * msg)
{
	int size;

	size = make_nm_msg_packet(tmp_buf, sizeof(tmp_buf), msg);

	if ( size <= 0 ) 
		return -1;

	return write(fd, tmp_buf, size);
}



