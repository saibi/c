#include <stdio.h>

void even_odd(int param);

void even_odd(int param)
{
	if ( (param % 2 ) == 0 ) 
		printf("even\n");
	else
		printf("odd\n");
}
