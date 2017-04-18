#include <stdio.h>
#include <stdlib.h>

void main(void)
{
	char tmp[128] = "1.30rc2";

	float ver;

	ver = atof(tmp);

	printf("%.10f\n", ver);
	if ( ver == 1.3 ) {
		printf("%f < 1.3 true???\n", ver);
	} else {
		printf("ok\n");
	}

}
