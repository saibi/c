/*!
  \file checksum.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Dec 08 18:59:26 KST 2010

*/
#include <checksum.h>

/// checksum 계산 
/// \param buf 
/// \param size
/// \return checksum
int calc_checksum(unsigned char *buf, int size)
{
	unsigned short checksum = 0;
	int i;

	for ( i = 0; i < size ; i++) {
		checksum += buf[i];
	}
	return checksum;
}
/********** end of file **********/
