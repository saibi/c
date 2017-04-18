/*!
 * \file token.c
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 금 4 04  Korea Standard Time 2008
 *
*/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PARSE_PARAM_OPT_SKIP_NULL 0x01

/// 문자열을 delimeter 로 구분한 후 사용자가 원하는 위치의 token 을 얻어온다
/// \param src 원본 문자열
/// \param del delimeter 문자열 
/// \param pos 얻어올 위치 (1부터 시작)
/// \param buf (out) token 이 저장될 buffer
/// \param buf_size buffer 크기 
/// \return position_pointer 원본 문자열에서 token 의 위치
/// \return NULL token 을 얻을 수 없음 
char * extract_token(char *src, char *del, int pos, char *buf, int buf_size)
{
	char *token_start = src;
	char *token_end = src;
	int i;
	int del_len = strlen(del);
	int token_len;
	
	for ( i = 0 ; i < pos ; i ++ ) {
		if ( (token_end = strstr( token_end, del )) != NULL) {
			if ( i == pos - 1 ) {
				token_len = (int)(token_end - token_start);
				
				if ( token_len > buf_size ) {
					strncpy(buf, token_start, buf_size);
					buf[buf_size -1] = 0;
				} else {
					strncpy(buf, token_start,(int)(token_end - token_start));
				}
				buf[token_len] = 0;
				return token_start;
			} else {
				token_start = (char *)(token_end + del_len);
				token_end += del_len;
			}
		} else {
			if ( i == pos - 1 ) {
				strncpy(buf, token_start, buf_size);
				buf[buf_size-1] = 0;
				return token_start;
			} else {
				return NULL;
			}
		}
	}
	return NULL;
}


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
		if ( isdigit(*fmt) ) {
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
		while( isspace(*fmt) ) {
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
					*((int *)paddr) = atoi(token);
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
                                	*((short *)paddr) = atoi(token);
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
					*((char*)paddr) = atoi(token);
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

int main(int argc, char *argv[])
{
	char buf[128] = "B;CF;-20.00;0.00;1.00;;;;;F;;;;A1;;;;;;HV1g1";
	char tmp[128], gr[128], hv[128];
	float f;
	int i;

	int ret;

	set_parse_param_sep_str(";");

	ret = parse_param(buf, "ssfffssfisffsss20 sssss s20", tmp,tmp,&f,&f,&f, tmp,tmp,&f,&i,tmp, &f,&f,tmp,tmp,gr, tmp,tmp,tmp,tmp,tmp, hv);

	printf("ret = %d\n", ret);

	return 0;
}

/********** end of file **********/

