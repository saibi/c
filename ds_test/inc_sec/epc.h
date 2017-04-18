/*!
 * \file epc.h
 * \brief
 *
 * excelon <-> pc
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : ±Ý  6¿ù 23 17:05:41 KST 2006
 *
*/
#ifndef _EPC_H_
#define _EPC_H_


#define EPC_CODE_SIZE 4
#define EPC_HEADER_SIZE 8

struct epc_header {
	char code[EPC_CODE_SIZE];
	int size;
};


#define EPC_CODE_EXCELON_SCREEN_SHOT "SS00"
#define EPC_CODE_EZ_SCREEN_SHOT "SS01"
#define EPC_CODE_FRAME_DATA "FRDT"
#define EPC_CODE_EZ_TFT_SCREEN_SHOT "SS02"
#define EPC_CODE_HEX_SCREEN_SHOT "SS03"

// CPE-4000 frame backup
#define EPC_CODE_DUMP "DUMP" 
#define EPC_CODE_FB_JOB "FJOB" // job numer
#define EPC_CODE_FB_DATA "FDAT" // job_no, crc, data
#define EPC_CODE_FR_ALL "FRAL" // read all 



#define send_epc_header(uart, header) uart_write_b(uart, (header),  EPC_HEADER_SIZE)


char *make_epc_header_str( char *code, int size);

#endif
/********** end of file **********/
