/*!
 * \file epc_comm_sub.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 금 1 16  대한민국 표준시 2009
 *
*/
#ifndef _EPC_COMM_SUB_H_
#define _EPC_COMM_SUB_H_

#include <epc_comm_frame.h>

int parse_n_check_trcfmt(char *fmt, int *p_record_format, int *p_side);
int parse_layout_copt(char *fmt, struct epc_comm_frame_data *param);
int parse_layout_opt(char *fmt, struct epc_comm_frame_data *param);
int parse_dp_opt(char *fmt, struct epc_comm_frame_data *param);
int parse_edging_opt(char *fmt, struct epc_comm_frame_data *param);
void zero_epc_comm_frame_data(struct epc_comm_frame_data *param, int count);
int parse_binary_float_value(char *fmt, float *p_r, float *p_l);


/// epc frame data 에서 fc, cir 필드 복사 
/// \param src source 
/// \param dest (out) destination
static INLINE void copy_fc_cir_opt(struct epc_comm_frame_data *src, struct epc_comm_frame_data *dest)
{
	dest->frame_curve = src->frame_curve;
	dest->cir = src->cir;
}

/// epc frame data 에서 layout common option 필드 복사 
/// \param src source 
/// \param dest (out) destination
static INLINE void copy_layout_common_opt(struct epc_comm_frame_data *src, struct epc_comm_frame_data *dest)
{
	dest->vision_mode = src->vision_mode;
	dest->bifocal_offset_h = src->bifocal_offset_h;
	dest->bifocal_offset_v = src->bifocal_offset_v;
	dest->bifocal_dia = src->bifocal_dia;
	dest->bridge_size = src->bridge_size;
	dest->blocking_mode = src->blocking_mode;
	dest->oh_type = src->oh_type;
}

/// epc frame data 에서 layout option 필드 복사 
/// \param src source 
/// \param dest (out) destination
static INLINE void copy_layout_opt(struct epc_comm_frame_data *src, struct epc_comm_frame_data *dest)
{
	dest->single_pd = src->single_pd;
	dest->delta_y = src->delta_y;
}

/// epc frame data 에서 dp option 필드 복사 
/// \param src source 
/// \param dest (out) destination
static INLINE void copy_dp_opt(struct epc_comm_frame_data *src, struct epc_comm_frame_data *dest)
{
	dest->dp_down = src->dp_down;
	dest->dp_updown = src->dp_updown;
	dest->dp_leftright = src->dp_leftright;
	dest->dp_radius = src->dp_radius;
	dest->dp_percent = src->dp_percent;
	dest->dp_rotate = src->dp_rotate;
}

/// epc frame data 에서 edging option 필드 복사 
/// \param src source 
/// \param dest (out) destination
static INLINE void copy_edging_opt(struct epc_comm_frame_data *src, struct epc_comm_frame_data *dest)
{
	dest->fragile_mode = src->fragile_mode;
	dest->lens_material = src->lens_material;
	dest->edging_type = src->edging_type;
	dest->polish = src->polish;
	dest->sb_front = src->sb_front;
	dest->sb_rear = src->sb_rear ;
	dest->pos_type = src->pos_type;
	dest->pos_value = src->pos_value;
	dest->size = src->size;
	dest->grooving_depth = src->grooving_depth;
	dest->grooving_width = src->grooving_width;
}


extern char epc_comm_cr_str[4];

void change_epc_comm_cr_str(char *str);

#define SET_DEFAULT_EPC_COMM_CR_STR() change_epc_comm_cr_str(ISO16284_STR_CODE_CR)
#define SET_TEXT_EPC_COMM_CR_STR() change_epc_comm_cr_str("\n")


#endif
/********** end of file **********/
