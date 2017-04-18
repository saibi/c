#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <ssl_common.h>
#include "ascii_diff.h"
#include "data.h"


static int get_value2(char *buf, char *value)
{
	char *eq;

	eq = strstr(buf, "=");
	if ( eq == NULL ) 
	{
		return -1;
	}

	for ( ++eq; *eq == ' '; eq++)
		;

	for ( ; *eq != 0 ; eq++ )
	{
		*value++ = *eq;
	}
	*value = 0;
	return 0;
}



/// ASCII diff Record 분석 (R=xxx or A=xxx...)
/// mem_get_line() 함수를 사용한다. 
/// 첫 라인은 line parameter 로 넘겨줄것. 이 후 부터는 mem_get_line(NULL, ) 을 이용해 불러 온다.
/// \param first_line 첫 라인 
/// \param type record type (R = 0 or A = 1 ....) , see enum ascii_diff_type_idx {}
/// \param rev 0-normal/ 1-reverse
/// \param list (out)
/// \param max list 크기 (최대 저장 개수)
/// \return read_count
/// \return -ERR_INVAL 
int parse_ascii_diff_record(char *first_line, int type, int rev, float *list, int max)
{
	int count = 0;
	char line[1024] = {0, };
	char key[128];
	char value[128];
	char *ptr;
	int prev;
	int roll_back = 0;

	char *type_str[] = {
		RECORD_RADIUS_DATA,
		RECORD_ANGLE_DATA,
		RECORD_Z_DATA,
	};
	float convert_val[] = {
		1.0/BASELINE_MULTIPLIER,
		1.0/BASELINE_MULTIPLIER_FOR_ANGLE,
		1.0/BASELINE_MULTIPLIER,
	};

	strncpy(line, first_line, sizeof(line)-1);
	do {
		if ( count >= max ) {
			roll_back = 1;
			break;
		}

		// record 는 연속적으로 나와야 한다.
		if ( line[0] == 0 ) {
			continue;
		}
		if ( line[0] == CHAR_RS || line[0] == CHAR_GS) {
			SSL_PRINTF("parse_ascii_diff_record() : End of packet. record count = %d\n", count);
			roll_back = 1;
			break;
		}

		if ( get_key(line, key) < 0 ) {
			SSL_PRINTF("parse_ascii_diff_record() : Wrong record. record count = %d\n", count);
			roll_back = 1;
			break;
		}

		if ( strcmp(key, type_str[type]) != 0 ) {
			SSL_PRINTF("parse_ascii_diff_record() : Wrong label. record count = %d\n", count);
			roll_back = 1;
			break;
		}

		get_value2(line, value);
		SSL_PRINTF("#%d value [%s]\n", count, value);

		ptr = strtok(value, ISO16284_STR_FSEP);
		if ( !ptr ) {
			continue;
		}
		prev = atoi(ptr);
		list[count] = (float)prev * convert_val[type];
		count++;

		if ( rev ) {
			// ascii diff reverse
			while ( (ptr = strtok(NULL, ISO16284_STR_FSEP) ) != NULL ) {
				prev += atoi(ptr);
				list[count] = (float)prev * convert_val[type];
				count++;
			}
		} else {
			// ascii diff
			while ( (ptr = strtok(NULL, ISO16284_STR_FSEP) ) != NULL ) {
				SSL_PRINTF("#%d prev = %d\n", count, prev);
				prev -= atoi(ptr);
				list[count] = (float)prev * convert_val[type];
				count++;
			}
		}
	} while ( mem_get_line(NULL, line, sizeof(line)) > 0 );

	if ( roll_back) {
		mem_unget_line(NULL, line);
	}
	return count;
}


static void parse_angle(char *buf, float *list)
{
	char epc_comm_cr_str[4] = ISO16284_STR_CODE_CR;

	char line_buf[1024];
	char key[1024];

	int ret = 0;
	char prev_sep[4] = {0, };

	int i;

	set_parse_param_sep_str( ISO16284_STR_FSEP );
	strncpy(prev_sep, GET_MEM_GET_LINE_SEP_STR(), sizeof(prev_sep));
	SET_MEM_GET_LINE_SEP_STR( epc_comm_cr_str );
	mem_get_line(buf, line_buf, 0); // buf 설정용 

	for ( i = 0 ; i < 1 ; i ++)
	{
		if ( mem_get_line(NULL, line_buf, sizeof(line_buf)) < 0 ) {
			break;
		}

		// DEBUG  buffer dump
		//SSL_PRINTF("DEBUG line : ");
		//SSL_PRINTF(line_buf);
		//print_iso16284_stream(line_buf);
		//SSL_PRINTF("\n");

		if ( line_buf[0] == CHAR_GS ) {
			break;
		}

		if ( line_buf[0] == CHAR_FS ) {
			//skip <FS>
			line_buf[0] = ' ';
		}

		if ( get_key(line_buf, key) < 0 ) {
			continue;
		}

		if ( (strcmp(key, RECORD_ANGLE_DATA) == 0 ) ) {
			if (  ( ret = parse_ascii_diff_record(line_buf, 1, 0, list, 1440)) < 0 ) {
				SSL_PRINTF("iso16824_to_epc_comm_frame_data() : R error. %d\n", ret);
				continue;
			} 
			SSL_PRINTF("record count = %d\n", ret);
			continue;
		}
	}
	SET_MEM_GET_LINE_SEP_STR( prev_sep );
	set_parse_param_sep_str(" ");
}

int main(void)
{
	float normal_list[1440] = { 0.0, };
	float reverse_list[1440] = { 0.0, };
	int i;

	printf("ASCII diff test\n");

	parse_angle(normal_angle, normal_list);
	parse_angle(reverse_angle, reverse_list);

	for ( i = 0 ; i < 1440; i++ )
	{
		SSL_PRINTF("[%d] %f %f\n", i, normal_list[i], reverse_list[i]);
	}
	return 0;
}


