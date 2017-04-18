/*!
 * \file epc_new_comm.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 목 1 15  대한민국 표준시 2009
 *
*/
#ifndef _EPC_NEW_COMM_
#define _EPC_NEW_COMM_

#include <epc_comm_frame.h>

#define EPC_OLD_VER 0 // cpe-4000 compatible
#define EPC_NEW_VER 1 // new version , dcs 3.07 호환 필드 사용 , huvitz 자체 필드는 REM 으로 wrapping

#define EPC_PREFIX "KYM_"
#define EPC_PREFIX_FULL "REM=KYM_"
#define RECORD_VER "VER"


#define DCSR_FTYP "FTYP" // frame type FTYP=2
#define DCSR_MPD "MPD" // fpd MPD=70.4
#define DCSR_DBL "DBL" // bridge size, distance between lenses , DBL=19.0
#define DCSR_CIRC3D "CIRC3D" // circumference (3d) CIRC3D=12.0;23.0
#define DCSR_FCRV "FCRV" // frame curv FCRV=2.5;2.4
#define DCSR_IPD "IPD" // single pd IPD=32.0;31.0
#define DCSR_ETYP "ETYP" // edging type
#define DCSR_GWIDTH "GWIDTH" // groove width
#define DCSR_GDEPTH "GDEPTH" // groovedepth 
#define DCSR_POLISH "POLISH" // 
#define DCSR_LMATTYPE "LMATTYPE" // lens material


int del_epc_prefix(char *buf);
int epc_comm_frame_data_to_iso16284(char *buf, struct epc_comm_frame_data *param, int count);
int epc_comm_frame_data_to_iso16284_v1(char *buf, struct epc_comm_frame_data *param, int count);
int iso16284_to_epc_comm_frame_data(char *buf, struct epc_comm_frame_data *param, int count, struct epc_drill_data **p_drill, int *drill_count);

#endif
/********** end of file **********/
