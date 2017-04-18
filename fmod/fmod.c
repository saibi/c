#include <stdio.h>
#include <math.h>

int main(void)
{
	printf("fmod = %.3f\n", fmod(733.4, 360.0));
	printf("fmod = %.3f\n", fmod(293.33, 360.0));
	printf("fmod = %.3f\n", fmod(-20.8, 360.0));
	printf("fmod = %.3f\n", fmod(-365.3, 360.0));

	return 0;
}

