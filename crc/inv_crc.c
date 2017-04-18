/*!
  \file inv_crc.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : 2016/01/11 15:04:22 (KST)

*/

#include <stdio.h>

#include "inv_crc.h"

#define PR printf 

/// Calc CRC
static unsigned short AddData(unsigned short crc, unsigned short data)
{
	unsigned short out,i;
	out = crc^data;
	for(i=0;i<8;i++){
		if(out&1) out= (out>>1)^0xa001;
		else
			out= out>>1;
	}
	return out;
}

/// Calc CRC
static unsigned short GetCRC(unsigned char * data, int len)
{
	unsigned short wSeed,i;
	wSeed = 0xffff;
	for(i=0;i<len;i++){
		wSeed = AddData(wSeed,*data++);
	}
	return ((wSeed<<8)|(wSeed>>8));
}

/// fill crc value
/// \param msg (in/out) msg[6], msg[7]
void fill_inv_crc(char *msg)
{
	unsigned short crc;

	crc = GetCRC((unsigned char *)msg, 6);
	msg[6] = ( crc >> 8 ) & 0xff;
	msg[7] =  crc & 0xff;
}

/// check crc value 
/// \param msg
/// \param len  7 or 8
/// \param dbg_msg 1-print debug message
/// \return 0 ok
/// \return -1 crc error
int check_inv_crc(char *msg, int len, int dbg_msg)
{
	unsigned short crc;
	char calc[2];

	crc = GetCRC((unsigned char *)msg, len-2);
	calc[0] = (crc >> 8 ) & 0xff;
	calc[1] = crc & 0xff;

	if ( calc[0] != msg[len-2] || calc[1] != msg[len-1] ) {
		if ( dbg_msg ) {
			PR("Inverter packet CRC mismatch : rcv %x %x, calc %x %x\n", calc[0], calc[1], msg[len-2], msg[len-1]);
		}
		return -1;
	}
	return 0;
}

#if 0
/// DEBUG : CRC test
static void test_crc(void)
{
	unsigned char test[8] = { 0x01, 0x03, 0x12,	0x05,	0x00, 0x01, 0, 0 };
	unsigned char test2[8]={ 0x01, 0x03, 0x12,	0x01,	0x00, 0x01, 0xd0, 0xb2 };
	unsigned char test3[8] ={ 0x01, 0x13, 0x02, 0x10, 	0x00, 0x00,		0x00, 0x00 };
	unsigned char test4[8] ={ 0x01, 0x13, 0x01, 0x10, 	0x00, 0x00,		0x00, 0x00 };
	unsigned char test5[8] = { 0x01, 0x13, 0x06, 0x10, 	0x00, 0x00,		0x00, 0x00 };
	unsigned short ret;

	ret = GetCRC(test, 6);
	PR("crc = %d, %x, 0x%x 0x%x\n", ret, ret, ( ret >> 8) & 0xff, ret & 0xff );
	ret = GetCRC(test2, 6);
	PR("crc = %d, %x, 0x%x 0x%x\n", ret, ret, ( ret >> 8) & 0xff, ret & 0xff );
	ret = GetCRC(test3, 6);
	PR("crc = %d, %x, 0x%x 0x%x\n", ret, ret, ( ret >> 8) & 0xff, ret & 0xff );
	ret = GetCRC(test4, 6);
	PR("crc = %d, %x, 0x%x 0x%x\n", ret, ret, ( ret >> 8) & 0xff, ret & 0xff );
	ret = GetCRC(test5, 6);
	PR("crc = %d, %x, 0x%x 0x%x\n", ret, ret, ( ret >> 8) & 0xff, ret & 0xff );
}
#endif 

#define MAX_TRIAC_CMD_IDX 11
#define MAX_TRIAC_CMD_LEN 8

void main(void)
{
	unsigned char triac_packet_list[MAX_TRIAC_CMD_IDX][MAX_TRIAC_CMD_LEN] = {
	// command
	{ 0x01, 0x13, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 }, // Wheel Stop
	{ 0x01, 0x13, 0x02, 0x10, 0x32, 0x20, 0x00, 0x00 }, // Wheel Run Low
	{ 0x01, 0x13, 0x02, 0x10, 0x4e, 0x20, 0x00, 0x00 }, // Wheel Run High
	{ 0x01, 0x15, 0x02, 0x10, 0x00, 0x00, 0x00, 0x00 }, // Pump1 On
	{ 0x01, 0x15, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 }, // Pump1 Off
	{ 0x01, 0x17, 0x02, 0x10, 0x00, 0x00, 0x00, 0x00 }, // Pump2 On
	{ 0x01, 0x17, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 }, // Pump2 Off
	{ 0x01, 0x19, 0x02, 0x10, 0x00, 0x00, 0x00, 0x00 }, // Vaccum On
	{ 0x01, 0x19, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 }, // Vaccum Off

	{ 0x01, 0x03, 0x12, 0x07, 0x00, 0x01, 0x00, 0x00 }, // temperature
	{ 0x01, 0x03, 0x12, 0x09, 0x00, 0x01, 0x00, 0x00 }, // vibration

	};

	int i;

	for ( i = 0 ; i < MAX_TRIAC_CMD_IDX; ++i )
	{
		fill_inv_crc(triac_packet_list[i]);
		printf("%x %x\n", triac_packet_list[i][6], triac_packet_list[i][7]);
	}


}
	
/********** end of file **********/
