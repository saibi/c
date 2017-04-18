/*!
 * \file ez_sync.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : ¿ù  6¿ù 18 14:29:38 KST 2007
 *
*/
#ifndef _EZ_SYNC_H_
#define _EZ_SYNC_H_

#include "epc_frame_data.h"


#define EZ_SYNC_FLAG_CURRENT_SIDE 0x01
#define EZ_SYNC_FLAG_BRIDGE_SIZE 0x02
#define EZ_SYNC_FLAG_VISION_MODE 0x04
#define EZ_SYNC_FLAG_BLOCKING_MODE 0x08
#define EZ_SYNC_FLAG_R_SINGLE_PD 0x10
#define EZ_SYNC_FLAG_L_SINGLE_PD 0x20
#define EZ_SYNC_FLAG_R_DELTA_Y 0x40
#define EZ_SYNC_FLAG_L_DELTA_Y 0x80
#define EZ_SYNC_FLAG_BIFOCAL_DIA 0x0100
#define EZ_SYNC_FLAG_BIFOCAL_OFFSET_H 0x0200
#define EZ_SYNC_FLAG_BIFOCAL_OFFSET_V 0x0400
#define EZ_SYNC_FLAG_PD_TYPE 0x0800

#define EZ_SYNC_FLAG_ALL (0xffff)



struct ez_sync_data {
	int flag; 
	int current_side; // 0 - R, 1 - L
	float bridge_size; // 18.00
	int vision_mode; // 0 - far, 1 - bifocal, 2- bifocal(circle, blend)
	int blocking_mode; // 0-boxing_center, 1-optical
	int pd_type; // 0 - pd, 1-single
	float single_pd[MAX_FRAME_SIDE]; // 32.00, 32.00
	float delta_y[MAX_FRAME_SIDE]; // 2.0, 2.0
	float bifocal_dia; // 24.00
	float bifocal_offset_h; // 5.00
	float bifocal_offset_v; // 5.00
};


int send_ez_sync_data(int uart, char *job_no, struct ez_sync_data *pdata);
int recv_ez_sync_data(int uart, char *packet_buf, int packet_size, char *job_no, struct ez_sync_data *pdata);

#endif
/********** end of file **********/
