
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHAR_CR 0x0D
#define CHAR_LF 0x0A

static void eat_LF(char *buf)
{
	char tmp_buf[4096];
	int i = 0, k = 0;

	while ( buf[i] != 0 ) {
		if ( buf[i] != CHAR_LF ) {
			tmp_buf[k++] = buf[i];
		}
		i++;
	}
	tmp_buf[k] = 0;

	strcpy(buf, tmp_buf);
}


int main(void)
{
	char tmp[100] = { CHAR_LF, '1','2', CHAR_CR, '3', 0,  };

	eat_LF(tmp);

	printf("%s\n", tmp);
	return 0;
}
