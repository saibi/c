#include <string.h>
#include <stdio.h>


struct meta {
	int front[1440];
	int rear[1440];
	short fr[1440];

};

struct meta a, *ptr;

#define CURRENT (ptr)

int main(int argc, char *argv[])
{
	memset(&a, 0, sizeof(a));


	ptr = &a;


	printf("sizeof(a) = %d\n", sizeof(a));
	printf("sizeof(rear) = %d\n", sizeof(CURRENT->rear));
	printf("sizeof(fr) = %d\n", sizeof(CURRENT->fr));


	return 0;
}


