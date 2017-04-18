#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ssl_common.h>

#define DP printf
#define DRILL_RETOUCH_FILE_KEY_STR "drill_retouch"

#define JOB_NO_LEN 128

#define SIDE_R 0
#define SIDE_L 1

typedef struct drill_retouch_file_rec {
	int id;
	char job_no[JOB_NO_LEN];
	int side;

} DRILL_RETOUCH_FILE;


void *Uart_Printf=(void*)printf;

/// get format version number
/// \return version
/// \return 1 (default)
static int get_data_file_format_version(char *header)
{
	char line[128] = {0 , };
	char *p;

	strncpy(line, header, sizeof(line));

	p = strchr(line, ';');
	if ( p == NULL ) {
		return 1;
	}
	*p = 0;

	p = strchr(line, 'V');
	if ( p == NULL ) {
		p = strchr(line, 'v');
		if ( p == NULL ) {
			return 1;
		}
	}

	p++;
	return atoi(p);
}

/// parsing drill retouch file header
/// \param buf
/// \param buf_size
/// \param p_dr (out) drill retouch file 
/// \return drill_count 
static int parse_drill_retouch_file(char *buf, int buf_size, DRILL_RETOUCH_FILE *p_dr)
{
	char line[128] = {0 , };
	char *p;
	int ret;
	int id = 0;
	char job_no[JOB_NO_LEN] = {0, };
	char side_str[16] = {0, };
	int side = 0;
	int ver = 1;

	p = (char*)memchr(buf, '#', buf_size);
	if ( p == NULL ) {
		return -ERR_FORMAT;
	}
	p++;
	mem_get_line(p, line, sizeof(line));
	DP("line=[%s]\n", line);
	if ( strstr(line, DRILL_RETOUCH_FILE_KEY_STR) == NULL ) {
		return -ERR_FORMAT;
	}
	ver = get_data_file_format_version(line);
	DP("ver = %d\n", ver);
	
	set_parse_param_sep_str(";");
	ret = parse_param(line, "siss", NULL, &id, job_no, side_str );
	set_parse_param_sep_str(" ");
	if ( ret < 4 ) {
		return -ERR_FORMAT;
	}

	ltrim(job_no);
	rtrim(job_no);
	if ( strstr(side_str, "R") || strstr(side_str, "r") || strstr(side_str, "0") ) {
		side = SIDE_R;
	} else {
		side = SIDE_L;
	}

	if ( p_dr ) {
		p_dr->id = id;
		p_dr->side = side;
		strncpy(p_dr->job_no, job_no, JOB_NO_LEN);
	}


	DP("id=%d, jon_no[%s], side=%d\n", id, job_no, side);

	return 0;
}

int main(void)
{
	char buf[128] = {
		"# drill_retouch V1;001;12345;R\n"
		"DRILLE=B;CF;-26.20;-1.30;1.00;-24.20;-1.30;;;;F;;;;;\n"
	};

	DRILL_RETOUCH_FILE d;
	int ret;

	ssl_set_printf_func(printf);
	printf("test\n");
	ret = parse_drill_retouch_file(buf, strlen(buf), &d);
	printf("ret = %d\n", ret);
	return 0;
}

/********** end of file **********/
