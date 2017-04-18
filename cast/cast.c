/*!
  \file float.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : ȭ 12 11 18:42:43 KST 2012

*/
#include <stdio.h>


static int read_sensor(void)
{
	return 370;
}

/// tester main
int main(void)
{
	int now;
	float f;

	now = (float)read_sensor() * 0.6;
	printf("now = %d\n", now);

	f = read_sensor();
	now = f * 0.6;
	printf("now = %d\n", now);

	now = read_sensor() * 6 / 10;
	printf("now = %d\n", now);


	return 0;
}
