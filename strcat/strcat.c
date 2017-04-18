#include <stdio.h>
#include <string.h>

int main(void)
{
	char dest[128];

	strcpy(dest, "sensor ");

	strcat(&dest[7], "x_pi-1023");

	printf("dest = [%s]\n", dest);

	return 0;
}
