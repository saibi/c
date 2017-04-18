/*!
  \file search.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Tue Mar 13 21:29:48 KST 2012

*/
#include <stdio.h>
#include <string.h>

#define CHAR_LSEP '='
#define CHAR_CR 0x0a
#define RECORD_REQUEST_TYPE "REQ"
#define RECORD_ANSWER_TYPE "ANS"
#define MAX_REQ_TYPE_LEN 32

/// search str
/// \param packet_buf
/// \param str
/// \return str_pointer
static char * search_req_str_in_the_packet(char *packet_buf, char *str)
{
	char tmp_buf[MAX_REQ_TYPE_LEN * 8] = { 0, };
	char *pst, *p;

	strncpy(tmp_buf, packet_buf, sizeof(tmp_buf)-1);
	pst = tmp_buf;

	while ( (p = strstr(pst, str)) != NULL ) {
		if ( p[ strlen(str) ] == ' ' || p[ strlen(str) ] == CHAR_LSEP ) {
			return &packet_buf[ (int)p - (int)tmp_buf ];
		}
		pst += (strlen(str) + 1);
	}

	return p;
}

/// packet 에서 request type string 을 추출한다.
/// \param packet_buf packet (NULL terminated)
/// \param buf (out) request type string (호출쪽에서 메모리 확보할 것 )
/// \return 0 ok
/// \return 음수 에러
static int get_request_type_str(char *packet_buf, char *buf)
{
	char * start, *end;
	int len;

	if ( (start = search_req_str_in_the_packet(packet_buf, RECORD_REQUEST_TYPE)) == NULL ) {
		if ( (start = search_req_str_in_the_packet(packet_buf, RECORD_ANSWER_TYPE)) == NULL ) {
			return -1;
		}
	}

	if ( (start = strchr( start, CHAR_LSEP ) ) == NULL ) {
		return -2;
	}
	start ++;
	if ( (end = strchr( start, CHAR_CR ) ) == NULL ) {
		return -3;
	}

	len = ((int)end - (int)start);
	if ( len >= (MAX_REQ_TYPE_LEN-1) ) {
		len = MAX_REQ_TYPE_LEN-1;
	}
	strncpy(buf, (char*)start, len);
	buf[ len ] = 0;
	return 0;
}


int main(void)
{
	char *src = "ANS=993444\n=c8c8\nc8fsksdafjaksekjfjlk\nREQQQ=2348234\nDO=B\nETYP=3\n";
	char buf[128] = { 0 , };


	char *p;

	p = search_req_str_in_the_packet(src, "RE");
	if ( p ) {
		printf("%s\n", p);
	}

	if ( get_request_type_str(src, buf) == 0 ) {
		printf("buf=%s\n", buf);
	}
	return 0;
}

