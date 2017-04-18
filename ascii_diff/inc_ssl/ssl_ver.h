/*!
 * \file ssl_ver.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : ¸ñ 4 03  Korea Standard Time 2008
 *
*/
#ifndef _SSL_VER_H_
#define _SSL_VER_H_

#define SSL_VERSION_STR "0.2.8"
// 0.2.8 20140616 ~ : 
// 0.2.7 20140514 ~ 20140520 fix parse_param() single param bug
// 0.2.6 20140409 ~  20140513 modify cmd_proc
// 0.2.5 20140404 ~ 20140409 import dictator calc code
// 0.2.4 import dictator common code (data convert ...)
// 0.2.3 import dictator code (iniparser)
// 0.2.2 import dictator code (uthash, nib, nsym ...)
// 0.2.1 20140213 fix mem_printf alloc/free bug
// 0.2 20140212 (xmc4500 test)
// 0.1 ~ 20140127 (dictator, spadework, hpe7000_motor ....)


void get_ssl_version_str(char *pstr);

#endif 
/********** end of file **********/
