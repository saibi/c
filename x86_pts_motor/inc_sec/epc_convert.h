/*!
 * \file epc_convert.h
 * \brief
 *
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 화  7월 04 11:14:33 KST 2006
 *
*/
#ifndef _EPC_CONVERT_H_
#define _EPC_CONVERT_H_



#define TYPE_CONVERT_END_VAL (-0x20118279)

// 각 자료구조간 필드 값 converting 을 위한 구조체
struct type_convert_list {
	int epc;
	int other;
};

extern struct type_convert_list epc_frame_type_2_iso16284_conv_list[];




int epc_type_to_other(struct type_convert_list *list, int epc);
int other_type_to_epc(struct type_convert_list *list, int other);

#define ISO16284_FRAME_TYPE_TO_EPC( iso16284 ) other_type_to_epc( epc_frame_type_2_iso16284_conv_list, iso16284)
#define EPC_FRAME_TYPE_TO_ISO16284( epc ) epc_type_to_other( epc_frame_type_2_iso16284_conv_list, epc)



#endif
/********** end of file **********/
