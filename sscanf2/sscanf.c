/*!
  \file sscanf.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Tue Oct 11 20:08:07 KST 2011

*/
#include <stdio.h>



int main(void)
{
	char ch = 0;
	int val = -1;
	int ver = 1;

	//sscanf("#B T I$", "#B T %c=%d$", &ch, &val);
	sscanf("#B T L=0$", "#B T %c=%d$", &ch, &val);

	printf("ch = %c, val = %d\n", ch, val);

	sscanf("feeler data V1;123", "feeler data V%d;%d", &ver, &val);
	printf("%d %d\n", ver, val);

	sscanf("feeler data;456", "feeler data V%d;%d", &ver, &val);
	printf("%d %d\n", ver, val);
	return 0;
}
/********** end of file **********/
