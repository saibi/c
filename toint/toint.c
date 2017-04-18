#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

struct {
	char src[128];
} g;

char * src = "PACHA#38.33c8c8c8c8";

#define CONF_MAGIC_NUM "PACHA"

int main(void)
{
	int ver = 0;
	long new_ver = 0;

	strcpy(g.src, "PACHA#38.33c8c8c8c8");

	char *endptr;
	if ( strncmp(g.src, CONF_MAGIC_NUM, 5) == 0 )
	{

		if ( strlen(g.src) > 6 ) 
		{
			sscanf(g.src, "PACHA#%d", &ver);

			new_ver = strtol(&g.src[6], &endptr, 10);
			if ( errno == 0 ) 
			{
				printf("ok new_ver = %d\n", (int)new_ver);
			}
		}

		printf("g.src : %s\n", g.src);
		printf("ver : %d\n", ver);

	}

	printf("end\n");
	return 0;
}
	
