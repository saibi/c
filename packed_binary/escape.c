/*!
  \file escape.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Aug 10 11:00:33 KST 2011

*/
#include <escape.h>

/// VCA DCS reserved character 인가?
/// \return 1 yes
/// \return 0 no
static int vca_dcs_is_reserved_char(int ch) 
{
	// 20110711 old code  복원 
	if (ch == CHAR_FS || ch == CHAR_GS || ch == CHAR_DC1 ||
		ch == CHAR_DC3 || ch == CHAR_ACK || ch == CHAR_NAK ||
		ch == CHAR_ESC || ch == CHAR_RS || ch == CHAR_SUB ||
		ch == CHAR_CR || ch == CHAR_LF || ch == CHAR_FSEP ||
		ch == CHAR_LSEP || ch == CHAR_CSEP ||
		ch == CHAR_MFLAG || ch == CHAR_UNKNOWN) {
		return 1;
	}
	return 0;
}

/// escape packed data
/// \param dest (out)
/// \param src
/// \param src_size
/// \return escaped_size
int escape(char *dest, char *src, int src_size)
{
	int i, k;

	for ( i = 0, k = 0 ; i < src_size ; i++, k++ ) {
		if ( ( src[i] < 32 ) && vca_dcs_is_reserved_char( src[i] ) ) {
			dest[k++] = CHAR_ESC;
			dest[k] = src[i] | 0x80;
		} else {
			dest[k] = src[i];
		}
	}
	return k;
}

/// unescape packed data
/// \param dest (out)
/// \param src
/// \param src_size
/// \return unescaped_size
int unescape(char *dest, char *src, int src_size)
{
	int i, k;

	for ( i = 0, k = 0 ; i < src_size ; i++, k++ ) {
		if ( src[i] == CHAR_ESC ) {
			i++;
			dest[k] = src[i] & 0x7f;
		} else {
			dest[k] = src[i];
		}
	}
	return k;
}
/********** end of file **********/
