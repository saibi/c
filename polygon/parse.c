#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ssl_common.h>

#define DP printf

typedef struct {
	int bevel_type;
	float front_height;
	float rear_height;
	float semi_u_x_offset;
	int pgrv_type;
	float pgrv_start;
	float pgrv_end;
} EDGING_DATA;


#define BEVEL_TYPE_NORMAL 0
#define BEVEL_TYPE_ASYMMETRIC 1
#define BEVEL_TYPE_MINI 2
#define BEVEL_TYPE_SEMI_U 3
#define BEV_FRONT_HEIGHT_MIN 0.0
#define BEV_FRONT_HEIGHT_MAX 0.8
#define BEV_REAR_HEIGHT_MAX 2.5
#define SEMI_U_X_OFFSET_MIN 0.0
#define SEMI_U_X_OFFSET_MAX 9.0
#define PGRV_TYPE_OFF 0
#define PGRV_TYPE_GRV_FLAT 1
#define PGRV_TYPE_GRV_BEV 2




/// parse HVBG field
/// \return 0 success
static int parse_HVBG(EDGING_DATA *dest , char *str)
{
	float first = 0.0;
	float second = 0.0;

	DP("parsing HVBG=%s\n", str);

	set_parse_param_sep_str(",");
	if ( parse_param(str, "iff iff", 
			&dest->bevel_type, &first, &second, 
			&dest->pgrv_type, &dest->pgrv_start, &dest->pgrv_end) < 2 ) { 
		set_parse_param_sep_str(" ");
		return -ERR_INVAL;
	}
	set_parse_param_sep_str(" ");

#ifdef _DICTATOR_EDGER_
	if ( debug_flag & DEBUG_FLAG_HVBG ) {
		// emulate bev/pgrv parameters
		DP("emulate bev/pgrv parameters\n");
		dest->bevel_type = dbg_bevel_type;
		first = dbg_front_height;
		second = dbg_rear_height;
		dest->pgrv_type = dbg_pgrv_type;
		dest->pgrv_start = dbg_pgrv_start;
		dest->pgrv_end = dbg_pgrv_end;
	}
#endif 
		
	if ( dest->bevel_type == BEVEL_TYPE_ASYMMETRIC ) {
		dest->front_height = first;
		if ( dest->front_height < BEV_FRONT_HEIGHT_MIN ) {
			dest->front_height = BEV_FRONT_HEIGHT_MIN;
		}
		if ( dest->front_height > BEV_FRONT_HEIGHT_MAX ) {
			dest->front_height = BEV_FRONT_HEIGHT_MAX;
		}

		dest->rear_height = second;
		if ( dest->rear_height < dest->front_height ) {
			dest->rear_height = dest->front_height;
		}
		if ( dest->rear_height > BEV_REAR_HEIGHT_MAX ) {
			dest->rear_height = BEV_REAR_HEIGHT_MAX;
		}
	} else if ( dest->bevel_type == BEVEL_TYPE_MINI ) {
		dest->front_height = first; // use first value
		if ( dest->front_height < BEV_FRONT_HEIGHT_MIN ) {
			dest->front_height = BEV_FRONT_HEIGHT_MIN;
		}
		if ( dest->front_height > BEV_FRONT_HEIGHT_MAX ) {
			dest->front_height = BEV_FRONT_HEIGHT_MAX;
		}
		dest->rear_height = dest->front_height;
	} else if ( dest->bevel_type == BEVEL_TYPE_SEMI_U) {
		dest->semi_u_x_offset = first;
		if ( dest->semi_u_x_offset < SEMI_U_X_OFFSET_MIN ) {
			dest->semi_u_x_offset = SEMI_U_X_OFFSET_MIN;
		}
		if ( dest->semi_u_x_offset > SEMI_U_X_OFFSET_MAX ) {
			dest->semi_u_x_offset = SEMI_U_X_OFFSET_MAX;
		}

		dest->rear_height = second;
		if ( dest->rear_height < 0.0 ) { 
			dest->rear_height = 0.0;
		}
		if ( dest->rear_height > (SEMI_U_X_OFFSET_MAX - dest->semi_u_x_offset) ) {
			dest->rear_height = (SEMI_U_X_OFFSET_MAX - dest->semi_u_x_offset);
		}
	}
	DP("bevel_type = %d, front_height = %.2f, rear_height = %.2f, semi_u_x_offset = %.2f\n", dest->bevel_type, dest->front_height, dest->rear_height, dest->semi_u_x_offset);


	if ( dest->pgrv_type == PGRV_TYPE_GRV_FLAT || dest->pgrv_type == PGRV_TYPE_GRV_BEV ) {
		dest->pgrv_start = fmod(dest->pgrv_start, 360);
		dest->pgrv_end = fmod(dest->pgrv_end, 360);
		if ( dest->pgrv_start > 180.0 ) {
			dest->pgrv_start -= 360.0;
		} else if ( dest->pgrv_start < -180.0 ) {
			dest->pgrv_start += 360.0;
		}
		if ( dest->pgrv_end > 180.0 ) {
			dest->pgrv_end -= 360.0;
		} else if ( dest->pgrv_end < -180.0 ) {
			dest->pgrv_end += 360.0;
		}
	}

	DP("pgrv_type = %d, pgrv_start = %.2f, pgrv_end = %.2f\n", dest->pgrv_type, dest->pgrv_start, dest->pgrv_end);
	return 0;
}

int main(void)
{
	char buf[] = "1,0.7,1.3,1,-45.3,90.4";
	EDGING_DATA e;
	int ret;

	printf("test\n");

	memset(&e, 0, sizeof(e));
	ret = parse_HVBG(&e, buf);
	printf("ret = %d\n", ret);

	return 0;
}

/********** end of file **********/
