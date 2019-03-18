#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/// 왼쪽 공백 제거
/// \param buf (in/out) string pointer
static void ltrim(char *buf)
{
	char *start_ptr = buf;

	while (*buf && isspace(*buf)) {
		buf++;
	}
	if (start_ptr != buf) {
		strcpy(start_ptr, buf);
	}
}

/// 오른쪽 공백 제거
/// \param buf (in/out) string pointer
static void rtrim(char *buf)
{
	int len = strlen(buf);

	while (len > 0 && isspace(buf[len - 1])) {
		len--;
	}
	buf[len] = 0;
}

static int count_char(char *p, char ch)
{
	int cnt = 0;

	while ( *p )
	{
		if ( *p == ch )
			++cnt;
		++p;
	}

	return cnt;
}


/// convert seprated value string to int array
/// "1;2;3;4" -> pvalues[0]=1, pvalues[1]=2, ...
/// \param str
/// \param sep separater char 
/// \param pvalues (out) int value array (allocate enough buffer before calling)
/// \return count 
static int sep_value_str_to_int_array(char *str, char sep, int * pvalues)
{
	char *p;
	char *next_p;
	char *pv;
	char backup;
	int i = 0;

	p = str;
	
	for ( p = str; ; ++p)
	{
		next_p = strchr(p, sep);
		if ( next_p )
		{
			backup = *next_p;
			*next_p = 0;

			for ( pv = p ; *pv ; ++pv ) 
				if ( ! isspace(*pv) ) 
					break;

			if ( pv != next_p )
			{
				pvalues[i++] = atoi(pv);
			}
			*next_p = backup;
			p = next_p;
		}
		else
		{
			if ( strlen(p) > 0 ) 
			{
				for ( pv = p ; *pv ; ++pv ) 
					if ( ! isspace(*pv) ) 
					{
						pvalues[i++] = atoi(pv);
						break;
					}

			}
			break;
		}
	}

	return i;
}

static void parse_scrl(char *buf)
{
	char line[1024];
	char *p;
	int cnt = 0;
	int i;
	int *values;

	printf("[%s]\n", buf);

	strcpy(line, buf);
	p = line;

	ltrim(p);
	rtrim(p);

	if ( (p = strchr(p, '=')) == NULL )
		return;
	
	++p;
	ltrim(p);
	
	cnt = count_char(p, ';');

	values = (int*)malloc( sizeof(int) * (cnt + 1) );
	if ( values == NULL )
	{
		printf("insufficient memory\n");
		return;
	}

	i = sep_value_str_to_int_array(p, ';', values);
	
	printf("i = %d\n", i);

	for ( int k = 0 ; k < i ; ++k )
		printf("%d\n", values[k]);

	free(values);
}

int main(void)
{
	parse_scrl("  SCRL   =1,; 5   ;6;7;8;      10   ");
	parse_scrl(" SCRL   =  3;      ");
	parse_scrl(" SCRL = 5 ");
	parse_scrl("  SCRL   =1; ;4;  ;" );

	return 0;
}
