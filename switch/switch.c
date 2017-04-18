#include <stdio.h>


void main(void)
{

	int val;

	val = 1;

	switch(val)
	{
		case 1:
			printf("1\n");
			break;

		case 2:
			printf("2\n");
			break;

		default:
			printf("default\n");
			break;
	}



	val = 1;

	switch(val)
	{
		default:
		case 1:
			printf("1\n");
			break;

		case 2:
			printf("2\n");
			break;

	}

	val = 2;
	switch(val)
	{
		default:
		case 1:
			printf("1\n");
			break;

		case 2:
			printf("2\n");
			break;

	}


	val = 3;
	switch(val)
	{
		default:
		case 1:
			printf("1\n");
			break;

		case 2:
			printf("2\n");
			break;

	}



}
