#include <stdio.h>

int main(void)
{
	char *buf = "192.168.0.8:8277";
	unsigned char ip[4];
	unsigned short port;
	int ret;

	ret = sscanf(buf, "%hhu.%hhu.%hhu.%hhu:%hu", 
			&ip[0],  
			&ip[1],  
			&ip[2],  
			&ip[3],  
			&port);

	printf("ret = %d\n%d.%d.%d.%d:%d\n", ret, ip[0], ip[1], ip[2], ip[3], port);

	return 0;
}
/********** end of file **********/
