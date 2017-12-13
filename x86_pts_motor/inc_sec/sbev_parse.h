/*!
  \file sbev_parse.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : 2015/06/17 10:06:31 (KST)

*/
#ifndef _SBEV_PARSE_H_
#define _SBEV_PARSE_H_

#include <sbev_def.h>

STEP_BEVEL_DATA * iso16284_to_STEP_BEVEL_DATA(char *buf);
STEP_BEVEL_DATA * iso16284_to_STEP_BEVEL_DATA_all(char *buf, STEP_BEVEL_DATA_LIST *pl);

#endif
/********** end of file **********/
