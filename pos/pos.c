#include <stdio.h>
#include <math.h>


#define FEELER_SCALE		(4*3.141592/2000)
#define RECORD_COUNT 1440


#include "data.h"


// motor 에서 전송 받은 feeler encoder 값 
extern int feeler_data_front[RECORD_COUNT]; 
extern int feeler_data_rear[RECORD_COUNT];


// 가공 형상 radius 데이터 (angle 값 오름 차순으로 정렬되어야 한다)
extern float pattern[RECORD_COUNT];


// 각 포인트의 렌즈두께 저장 (나중에 계산을 편하기 위해 두께/2 를 저장함)
float feeler_lens_thick[RECORD_COUNT];

// 렌즈 타입 결과 저장, +렌즈이면 0, -렌즈이면 1
int lens_type_is_negative;

// 렌즈 최소 두게, 최대 두께 저장 (실제 두께 / 2)
float half_of_min_thickness = 1000.0, half_of_max_thickness = 0.0;

// 최종 가공 위치 
float designed_pattern_X[RECORD_COUNT];


float pos_value = 0.0; // 사용자가 입력한 위치 값


// 렌즈 두께 및 타입 계산 
void calc_lens_thick_and_type(void)
{
	int i;
	float temp_cen_of_min_thickness = 0.0, temp_cen_of_max_thickness = 0.0;

	for (i = 0; i < RECORD_COUNT ; i++) {
		feeler_lens_thick[i] = ((float) (feeler_data_front[i]) * FEELER_SCALE - (float) (feeler_data_rear[i]) * FEELER_SCALE) / 2.0; 

		if (half_of_min_thickness > feeler_lens_thick[i] ) {
			half_of_min_thickness = feeler_lens_thick[i];
			temp_cen_of_min_thickness = (feeler_data_front[i] * FEELER_SCALE + feeler_data_rear[i] * FEELER_SCALE) / 2.0;
		}
		if (half_of_max_thickness < feeler_lens_thick[i]) {
			half_of_max_thickness = feeler_lens_thick[i];
			temp_cen_of_max_thickness = (feeler_data_front[i] * FEELER_SCALE + feeler_data_rear[i] * FEELER_SCALE) / 2.0;
		}
	}

	if (temp_cen_of_max_thickness > temp_cen_of_min_thickness) {
		// positive lens
		lens_type_is_negative = 0;
	} else {
		// negative lens
		lens_type_is_negative = 1;
	}
}


// 전면 mm 
void calc_front_mm(void)
{
	int i;

	// 0.0 <= pos_value 

	for ( i = 0 ; i < RECORD_COUNT ; i++) {
		if ( pos_value < feeler_lens_thick[i]) {
			designed_pattern_X[i] = (float) (feeler_data_front[i]) * FEELER_SCALE - pos_value;
		} else {
			designed_pattern_X[i] = feeler_lens_thick[i];
		}
	}
}

// 후면 mm 
void calc_rear_mm(void)
{
	int i;

	// 0.0 <= pos_value 

	for ( i = 0 ; i < RECORD_COUNT ; i++) {
		if (pos_value < feeler_lens_thick[i] ) {
			designed_pattern_X[i] = (feeler_data_rear[i]) * FEELER_SCALE + pos_value ;
		} else {
			designed_pattern_X[i] = feeler_lens_thick[i];
		}
	}
}

// 전면 %
void calc_front_percent(void)
{
	int i;

	// 0.0 <= pos_value <= 100.0

	float tmp_percent = pos_value / 100.0;

	for ( i = 0 ; i < RECORD_COUNT ; i++) {
		designed_pattern_X[i] = (feeler_data_front[i] * FEELER_SCALE) * (1.0 - tmp_percent ) + (feeler_data_rear[i] * FEELER_SCALE) * tmp_percent;
	}
}

// basecurve
void calc_basecurve(void)
{
	int i;

	// 0 <= pos_value <= 10 


	if ( lens_type_is_negative ) {
		// Case of Concave Lens 
		for ( i = 0 ; i < RECORD_COUNT ; i++) {
			designed_pattern_X[i] = ((feeler_data_front[i] * FEELER_SCALE - half_of_min_thickness) * (10 - pos_value) + (feeler_data_rear[i] * FEELER_SCALE + half_of_min_thickness) * (pos_value)) / 10.;
		}

	} else {
		// Case of Convex Lens
		for ( i = 0 ; i < RECORD_COUNT ; i++) {
			designed_pattern_X[i] = ((feeler_data_front[i] * FEELER_SCALE - half_of_min_thickness) * (pos_value) + (feeler_data_rear[i] * FEELER_SCALE + half_of_min_thickness) * (10 - pos_value)) / 10.;
		}
	}
}


void calc_frame_curve(void)
{
	int i;

	// 0.0 < pos_value <= 10.0

	float pattern_Z[RECORD_COUNT];
	float temp_pattern_Z[RECORD_COUNT];
	float max_z = 0.0;
	float alpha = 0.5;
	float alpha_step = 0.25;
	float std_margin_front = 0.6;
	float std_margin_rear = 0.6;
	float temp_margin_front = 0.0;
	float temp_margin_rear = 0.0;
	float min_margin_front = 100.0;
	float min_margin_rear = 100.0;

	for ( i = 0 ; i < RECORD_COUNT ; i++) {
		pattern_Z[i] = (500.0 / pos_value ) - sqrt(((500.0 / pos_value ) * (500.0 / pos_value)) - (pattern[i] * pattern[i]));
		temp_pattern_Z[i] = -pattern_Z[i];
		if(max_z < temp_pattern_Z[i]) {
			max_z = temp_pattern_Z[i];
		}
	}

	alpha = 0.5;
	alpha_step = 0.25;
	for ( i = 0 ; i < RECORD_COUNT ; i++) {
		temp_pattern_Z[i] = temp_pattern_Z[i] - max_z;
	}
			
	while(1) {
		min_margin_front = 100.0;
		min_margin_rear = 100.0;
		
		for ( i = 0 ; i < RECORD_COUNT ; i++) {
			designed_pattern_X[i] = (temp_pattern_Z[i] * alpha) + (((feeler_data_front[i]*FEELER_SCALE + feeler_data_rear[i]*FEELER_SCALE) / 2.0) * (1 - alpha));
			
			temp_margin_front = feeler_data_front[i]*FEELER_SCALE - designed_pattern_X[i];
			temp_margin_rear = designed_pattern_X[i] - feeler_data_rear[i]*FEELER_SCALE;
			
			if(min_margin_front > temp_margin_front) {
				min_margin_front = temp_margin_front;
			}
			if(min_margin_rear > temp_margin_rear) {
				min_margin_rear = temp_margin_rear;
			}
		}
		
		if((std_margin_front + std_margin_rear) > (min_margin_front + min_margin_rear)) {
			alpha = alpha - alpha_step;
		}
		else if((std_margin_front + std_margin_rear) < (min_margin_front + min_margin_rear)) {
			alpha = alpha + alpha_step;
		}
		else {
			break;
		}
		alpha_step = alpha_step / 2.0;
		
		if(alpha_step < 0.00001)
			break;
	}

	for ( i = 0 ; i < RECORD_COUNT ; i++) {
		designed_pattern_X[i] = designed_pattern_X[i] + ((min_margin_front - min_margin_rear) / 2.0);
	}

}


int main(int argc, char *argv[])
{
	int i;

	printf("percent test\n");
	calc_lens_thick_and_type();

	pos_value = 50.0;
	calc_front_percent();

	for ( i = 0 ; i < RECORD_COUNT; i++) {
		printf("%.2f\n", designed_pattern_X[i]);
	}


	printf("frame curve test\n");
	pos_value = 0.1;
	calc_frame_curve();

	for ( i = 0 ; i < RECORD_COUNT; i++) {
		printf("%.2f\n", designed_pattern_X[i]);
	}
	return 0;
}
