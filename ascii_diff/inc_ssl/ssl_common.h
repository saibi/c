/*!
 * \file ssl_common.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : ¸ñ 4 03  Korea Standard Time 2008
 *
*/
#ifndef _SSL_COMMON_H_
#define _SSL_COMMON_H_

#ifdef _saibi_shady_library_
#include <external_func_proto.h>
#else 
#include "ssl_exclude_option.h"
#endif 

// common
#include <common_macro.h>
#include <ssl_ver.h>
#include <error.h>
#include <llist.h>
#include <ascii.h>

// etc
#include <ssl_etc.h>

// str
#include <ssl_string.h>

// support 
#include <printf_func.h>
#include <time_tick.h>
#include <debug_support.h>
#include <int_float.h>
#include <lz.h>
#include <mem_printf.h>
#include <salloc.h>
#include <ssl_alloc.h>
#include <symbol_table.h>
#include <symbol_func.h>
#include <utf8.h>
#include <cmd_proc.h>
#include <cmd_proc_sym.h>
#include <cib.h>
#include <regexp.h>
#include <cmd_q.h>
#include <point_in_polygon.h>
#include <crc.h>
#include <script.h>

// HW support
#ifndef _EXCLUDE_EC_
#include <eeprom_common.h>
#endif
#ifndef _EXCLUDE_CONS_
#include <console.h>
#endif 

// lcd support
#ifndef _EXCLUDE_LS_
#include <bitmap.h>
#include <load_eif.h>
#endif

#endif
/********** end of file **********/
