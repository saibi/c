/*!
  \file arg.c
  \brief

  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Oct 12 09:49:28 KST 2011

*/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


char tmp_packet[1024];

/// send error code list
/// \param cnt number of error code
/// \param ... error code list
/// \return packet_size
/// \return negative_value error
static int send_error_code_list(int cnt, ...)
{
	va_list ap;
	char str[128];
	int i;
	int val;

	sprintf(tmp_packet, "motorerrlist ");

	va_start(ap, cnt);
	for ( i = 0 ; i < cnt ; i ++ ) {
		val = (int)va_arg(ap, int);
		sprintf(str, "%d ", val);
		strcat(tmp_packet, str);
	}
	va_end(ap);

	return 0;
}


/// tester main
int main(void)
{
	printf("stdarg test\n");

	send_error_code_list(1, 10);
	send_error_code_list(3, 1, 2, 3);
	send_error_code_list(10, 18, 28, 38, 1, 2, 10, 20, 30, 40, 50);
	send_error_code_list(2, 100, 200, 300);
	send_error_code_list(4, 100);

	printf("test end\n");
	return 0;
}
/********** end of file **********/
