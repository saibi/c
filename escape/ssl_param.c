/*!
 * \file ssl_param.c
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 화 4 22  Korea Standard Time 2008
 *
*/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ssl_common.h>

// internal prototype
int parse_param_get_max_string_length(char *fmt, int *p_max);

// parameter field separator string
// default " "
char field_sep_str_4_parse_param[32] = " ";

// option
int parse_param_option;

/// option 설정
/// \param opt
void set_parse_param_opt(int opt)
{
	parse_param_option = opt;
}

/// option return
/// \return option
int get_parse_param_opt(void)
{
	return parse_param_option;
}


/// field separator 설정
/// \param sep_str
void set_parse_param_sep_str(char *sep_str)
{
	if ( sep_str ) {
		strncpy(field_sep_str_4_parse_param, sep_str, sizeof(field_sep_str_4_parse_param));
		field_sep_str_4_parse_param[ sizeof(field_sep_str_4_parse_param) -1] = 0;
	} else {
		sprintf(field_sep_str_4_parse_param, " ");
	}
}

/// get max string length (include null character)
/// "s4ifff" -> 4, "sfffii" -> 0 
/// \param fmt
/// \param p_max (out) max length
/// \return inc_count
int parse_param_get_max_string_length(char *fmt, int *p_max)
{
	char tmp[32] = "0";
	int i = 0;

	fmt++;
	while( *fmt != 0 ) {
		if ( ssl_isdigit(*fmt) ) {
			tmp[i++] = *fmt++;
		} else {
			break;
		}
	}
	*p_max = atoi(tmp);
	return i;
}

/// string paramerter parsing
/// 20080704 코드 수정 : 기존 strtok() 대신 extract_token() 함수로 변경 , strtok() 를 다른 곳에서 이미 사용하고 있는 상태에서 parse_param() 을 호출할 경우 발생하는 오동작을 막기위해 
/// \param p_src 
/// \param fmt format string "iswcbfd", i - 4bytes integer, s - string, w - 2bytes integer, c - 1 byte character, b - 1 byte integer, f - 4bytes float, d - 8bytes double
/// \param ... argument list
/// \return number_of_arguments_processed
int parse_param(char *p_src, char *fmt, ...)
{
        va_list arg_list;
	char token[1024];
        int i = 0;
	void *paddr;
	int skip = 0;
	int max = 0, inc = 0;

        if ( !fmt) {
                return 0;
        }

        va_start(arg_list, fmt);

	for ( i = 1 ; extract_token(p_src, field_sep_str_4_parse_param, i, token, sizeof(token)) != NULL && *fmt; i++, fmt++ ) {

		// space 무시 
		while( ssl_isspace(*fmt) ) {
			fmt++;
		}
		if (! ( *fmt ) ) {
			break;
		}

		if ( token[0] == 0 && (parse_param_option & PARSE_PARAM_OPT_SKIP_NULL) ) {
			skip = 1;
		} else { 
			skip = 0;
		}
		
                switch(tolower(*fmt)) {
                        case 'i':
				paddr = (void*)va_arg(arg_list, int *);
				if ( !skip && paddr) {
					*((int *)paddr) = str2int(token);
				}
                                break;

                        case 's':
				paddr = (void*)va_arg(arg_list, char *);
				if ( !skip && paddr ) {
					inc = parse_param_get_max_string_length(fmt, &max);
					if ( max > 0 ) {
                                		strncpy((char*)paddr, token, max);
						fmt += inc;
					} else {
                                		strcpy((char*)paddr, token);
					}
				}
                                break;

                        case 'w':
                                paddr = (void*)va_arg(arg_list, short *);
				if ( !skip && paddr ) {
                                	*((short *)paddr) = str2int(token);
				}
                                break;

                        case 'c':
				paddr = (void*)va_arg(arg_list, char *);
				if ( !skip && paddr ) {
                                	*((char*)paddr) = token[0];
				}
                                break;

                        case 'b':
				paddr = (void*)va_arg(arg_list, char *);
				if ( !skip && paddr ) {
					*((char*)paddr) = str2int(token);
				}
                                break;

                        case 'f':
				paddr = (void*)va_arg(arg_list, float *);
				if ( !skip && paddr ) {
                                	*((float*)paddr) = atof(token);
				}
                                break;

                        case 'd':
				paddr = (void*)va_arg(arg_list, double *);
				if ( !skip && paddr ) {
					*((double*)paddr) = atof(token);
				}
                                break;
                }
        }
	va_end(arg_list);
        return i-1;
}
/********** end of file **********/

