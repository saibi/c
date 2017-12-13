/*!
  \file version.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : ±Ý  5 28 09:52:42 KST 2010

*/
#include <string.h>
#include <stdio.h>

#include <version.h>

char gui_version_str[MAX_VERSION_STR_LEN];
char version_str[MAX_VERSION_STR_LEN];

/// set gui version string (gui or edger gui ver)
/// \param str
void set_gui_version_str(char *str)
{
	memset(gui_version_str, 0, sizeof(gui_version_str));
	strncpy(gui_version_str, str, sizeof(gui_version_str)-1);
}

/// full version string
void make_version_str(void)
{
	sprintf(version_str, "%s_%s_B%s", VERSION_STR, DATE_STR, BUILD_COUNT_STR); 
}
/********** end of file **********/
