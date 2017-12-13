/*!
 * \file sec_ver.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : tue 5 13  Korea Standard Time 2008
 *
*/
#ifndef _SEC_VER_H_
#define _SEC_VER_H_

#define SEC_VERSION_STR "0.2.14"
// V0.2.14 : 20160810 8000x drill shape tilting field
// V0.2.13 : 20160708 8000x step bevel parameter, inclined cut 
// V0.2.12 : 20160425 fix step bevel fitting data parser 
// V0.2.11 : 20160412 step bevel fitting data 
// V0.2.10 : 20150918 fix drille huvitz field parser bug
// V0.2.9 : 20150821 add step bevel mode field (hpe8)
// V0.2.8 : 20150618 step bevel data , size optimization
// V0.2.7 : 20150609 add dcs fields (huvitz hab8 lens radius ...)
// V0.2.6 : 20150406 merge V0.1.4, hpe7000 edging param3 (hydrophobic mode related param...)
// V0.2.5 ~ : CRLF -> CR , merge v0.1.3 hi-polish
// V0.2.4 20140407 ~ 20140728 : change uart handler buffer alloc size (+1 byte)
// V0.2.3 20140407 dcs_macro.c -> dcs_macro.h
// V0.2.2 modify build packet routine (support hpe7800 circular uart buffer)
// V0.2.1 local buf -> alloc
// V0.2	20140205 inline -> func
// V0.1 ~20140205 

void get_sec_version_str(char *pstr);

#endif 
/********** end of file **********/
