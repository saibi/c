/*!
 * \file ssl_param_org.c
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 화 7 22  대한민국 표준시 2008
 *
*/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ssl_common.h>

extern char field_sep_str_4_parse_param[32];
extern int parse_param_option;
extern int parse_param_max_len;

// internal prototype
int parse_param_get_max_string_length(char *fmt, int *p_max);

/// string paramerter parsing, original code : using strtok() 
/// strtok() 과 충돌이 발생하지 않는 상활에서는 이 함수를 써라... 
/// \param p_src strtok() 에 사용되므로 constant string 을 사용하면 안된다.
/// \param fmt format string "iswcfd", i - 4bytes integer, s - string, w - 2bytes integer, c - 1 byte character, b - 1 byte integer, f - 4bytes float, d - 8bytes double
/// \param ... argument list
/// \return number_of_arguments_processed
int parse_param_org(char *p_src, char *fmt, ...)
{
        va_list arg_list;
        char *p;
        int i = 0;
	void *paddr;
	int skip = 0;
	int max, inc;

        if ( !fmt) {
                return 0;
        }

        p = strtok(p_src, field_sep_str_4_parse_param);
        if (!p ) {
                return 0;
        }
        va_start(arg_list, fmt);

        for (; p && *fmt; fmt++, p = strtok(NULL, field_sep_str_4_parse_param)) {
		// space 무시 
		while( ssl_isspace(*fmt) ) {
			fmt++;
		}
		if (! (*fmt) ) {
			break;
		}

		if ( p[0] == 0 && (parse_param_option & PARSE_PARAM_OPT_SKIP_NULL) ) {
			skip = 1;
		} else { 
			skip = 0;
		}

                switch(tolower(*fmt)) {
                        case 'i':
				paddr = (void*)va_arg(arg_list, int *);
				if ( !skip && paddr ) {
					*((int *)paddr) = str2int(p);
				}
                                break;

                        case 's':
				paddr = (void*)va_arg(arg_list, char *);
				if ( !skip && paddr ) {
					inc = parse_param_get_max_string_length(fmt, &max);
					if ( max > 0 ) {
                                		strncpy((char*)paddr, p, max);
						fmt += inc;
					} else {
                                		strcpy((char*)paddr, p);
					}
				}
                                break;

                        case 'w':
                                paddr = (void*)va_arg(arg_list, short *);
				if ( !skip && paddr ) {
                                	*((short *)paddr) = str2int(p);
				}
                                break;

                        case 'c':
				paddr = (void*)va_arg(arg_list, char *);
				if ( !skip && paddr ) {
                                	*((char*)paddr) = p[0];
				}
                                break;

                        case 'b':
				paddr = (void*)va_arg(arg_list, char *);
				if ( !skip && paddr ) {
					*((char*)paddr) = str2int(p);
				}
                                break;

                        case 'f':
				paddr = (void*)va_arg(arg_list, float *);
				if ( !skip && paddr ) {
                                	*((float*)paddr) = atof(p);
				}
                                break;

                        case 'd':
				paddr = (void*)va_arg(arg_list, double *);
				if ( !skip && paddr ) {
					*((double*)paddr) = atof(p);
				}
                                break;
                }
		i++;
        }
        return i;
}
/********** end of file **********/
