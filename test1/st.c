

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"


void convert_xy_to_r(float *r, float *a, float *x, float *y, int record_number);
void convert_r_to_xy(float *x, float *y, float *r, float *a, int record_number);
int rearrange_angle_data(float *radius_list, float *angle_list, int max);
void shift_center_xy(float *x, float *y, float delta_x, float delta_y, int record_number);

struct sort_data {
	int idx;
	struct list_head list;
};

#define SORT_FRAME_DATA_FLAG_RT 0x0
#define SORT_FRAME_DATA_FLAG_XY 0x1
#define SORT_FRAME_DATA_FLAG_ASC 0x0
#define SORT_FRAME_DATA_FLAG_DSC 0x2

int sort_frame_data_core(float *r_list, float *a_list, int max, int flag);

#define SORT_FRAME_DATA(r_list, a_list, max) sort_frame_data_core(r_list, a_list, max, SORT_FRAME_DATA_FLAG_RT)
#define SORT_XY_FRAME_DATA(x_list, y_list, max) sort_frame_data_core(x_list, y_list, max, SORT_FRAME_DATA_FLAG_XY)


#define ASSERT(x) 

#define CONST_PI 3.14159


enum err_idx {
	NO_ERR,
	ERR_NOMEM,

	MAX_ERR
};

/// 중심이동 (r theta  좌표)
/// \param r (out)
/// \param a (out)
/// \param delta_x
/// \param delta_y
/// \param record_number
void shift_center_r(float *r, float *a, float delta_x, float delta_y, int record_number)
{
	int i;
	float temp_x, temp_y;

	ASSERT(r != NULL && a != NULL );

	for (i = 0 ; i < record_number; i++) {
		temp_x = r[i] * sin(a[i]) - delta_x;
		temp_y = r[i] * cos(a[i]) - delta_y;

		r[i] = sqrt(temp_x * temp_x + temp_y * temp_y);
		a[i] = atan2(temp_x, temp_y);
		if ( a[i] < 0 ) {
			a[i] += (2*CONST_PI);
		}
	}
}

/// 중심이동 (xy 좌표)
/// \param x (out)
/// \param y (out)
/// \param delta_x
/// \param delta_y
/// \param record_number
void shift_center_xy(float *x, float *y, float delta_x, float delta_y, int record_number)
{
	int i;

	ASSERT( x != NULL && y != NULL);

	for (i = 0 ; i < record_number; i++) {
		x[i] -= delta_x;
		y[i] -= delta_y;
	}
}


/// frame 데이터 각도 순으로 정렬 (오름차순(default) 혹은 내림 차순))
/// \param r_list (in/out) r list or x list
/// \param a_list (in/out) a list or y list
/// \param max
/// \param flag 0x00 - r/theta data & 오름 차순, 0x01 - xy data, 0x02 - 내림 차순
/// \return 0 success
int sort_frame_data_core(float *r_list, float *a_list, int max, int flag)
{
	struct sort_data *idx_pool, *entry, *tmp_entry;
	int pool_idx = 0;
	int i, ins_flag = 0;
	struct list_head head, *p;
	float *src_r_list, *src_a_list;
	float *tmp_r_list, *tmp_a_list;

	INIT_LIST_HEAD(&head);

	idx_pool = (struct sort_data *)malloc( sizeof(struct sort_data) * max);
	src_r_list = (float *)malloc(sizeof(float) * max);
	src_a_list = (float *)malloc(sizeof(float) * max);
	tmp_r_list = (float *)malloc(sizeof(float) * max);
	tmp_a_list = (float *)malloc(sizeof(float) * max);
	if (idx_pool == NULL || tmp_r_list == NULL || tmp_a_list == NULL || src_r_list == NULL || src_a_list == NULL ) {
		printf("sort_frame_data() : insufficient memory.\n");

		if ( idx_pool ) {
			free(idx_pool);
		}
		if ( src_r_list) {
			free(src_r_list);
		}
		if ( src_a_list) {
			free(src_a_list);
		}
		if ( tmp_r_list) {
			free(tmp_r_list);
		}
		if ( tmp_a_list) {
			free(tmp_a_list);
		}

		return -ERR_NOMEM;
	}

	if ( flag & SORT_FRAME_DATA_FLAG_XY ) {
		convert_xy_to_r(src_r_list, src_a_list, r_list, a_list, max);
	} else {
		memcpy((char*)src_r_list, (char *)r_list, sizeof(float) * max);
		memcpy((char*)src_a_list, (char *)a_list, sizeof(float) * max);
	}


	for ( i = 0 ; i < max; i++ ) {
		entry = &idx_pool[pool_idx++];
		entry->idx = i;
		ins_flag = 0;

		list_for_each(p, &head) {
			tmp_entry = list_entry(p, struct sort_data, list);

			if ( (flag & SORT_FRAME_DATA_FLAG_DSC) ^ ( src_a_list[tmp_entry->idx] > src_a_list[entry->idx] ) ) { 
				list_add_tail(&entry->list, &tmp_entry->list);
				ins_flag = 1;
				//printf("DEBUG add [%d]%f before [%d]%f\n", entry->idx, a_list[entry->idx], tmp_entry->idx, a_list[tmp_entry->idx]);
				break;
			}
		}
		if ( !ins_flag ) {
			list_add_tail(&entry->list, &head);
			//printf("DEBUG add tail [%d]%f\n", entry->idx, a_list[entry->idx]);
		}
	}

	i = 0;
	list_for_each(p, &head) {
		tmp_entry = list_entry(p, struct sort_data, list);
		//printf("DEBUG [%d] %f\n", tmp_entry->idx, a_list[tmp_entry->idx]);
		tmp_r_list[i] = r_list[tmp_entry->idx];
		tmp_a_list[i] = a_list[tmp_entry->idx];
		i++;
	}

	memcpy((char*)r_list, (char*)tmp_r_list, sizeof(float) * max);
	memcpy((char*)a_list, (char*)tmp_a_list, sizeof(float) * max);

	free(idx_pool);
	free(src_r_list);
	free(src_a_list);
	free(tmp_r_list);
	free(tmp_a_list);

	return 0;
}


/// r theta 좌표 값 을 xy 좌표 값으로 변환 
/// \param x (out)
/// \param y (out)
/// \param r (in)
/// \param a (in)
/// \param record_number
void convert_r_to_xy(float *x, float *y, float * r, float * a, int record_number)
{
	int i;

	ASSERT( x != NULL && y != NULL && r != NULL && a != NULL);

	for (i = 0; i < record_number; i++) {
		x[i] = r[i] * sin(a[i]);
		y[i] = r[i] * cos(a[i]);
	}
}

/// xy 좌표 값을 r theta 좌표 값으로 변환 
/// \param r (out)
/// \param a (out)
/// \param x (in)
/// \param y (in)
/// \param record_number
void convert_xy_to_r(float *r, float *a, float *x, float *y, int record_number)
{
	int i;

	ASSERT( x != NULL && y != NULL && r != NULL && a != NULL);

	for ( i = 0 ; i <record_number; i++) {
		r[i] = sqrt( (x[i] * x[i]) + (y[i] * y[i]));

		a[i] = atan2(x[i], y[i]);
		if ( a[i] < 0.0 ) {
			a[i] += 2 * CONST_PI;
		} 
	}
}

/// 20080903 시작 angle index 찾아 오름차순으로 재정렬
/// 함수 이름은 sort 이지만 sort 와는 조금 다른 개념임
/// \paraqm radius_list (in/out)
/// \paraqm angle_list (in/out)
/// \param max
/// \return 0 success
int rearrange_angle_data(float *radius_list, float *angle_list, int max)
{
	int i;
	float *temp_pattern;
	float *temp_pattern_T;
	float tmp_angle_diff, max_angle_diff = 0.0, min_angle =10.0;
	int start_idx = 0;

	temp_pattern = (float*)malloc( sizeof(float) * (max + 1));
	temp_pattern_T = (float*)malloc( sizeof(float) * (max + 1));

	if ( temp_pattern == NULL || temp_pattern_T == NULL ) {
		printf("rearrange_angle_data() : insufficient memory\n");
		if ( temp_pattern) {
			free(temp_pattern);
		}
		if ( temp_pattern_T) {
			free(temp_pattern_T);
		}
		return -ERR_NOMEM;;
	}

	/* Sorting angle */

	memcpy((char*)temp_pattern, (char*)radius_list, sizeof(float) * max);
	memcpy((char*)temp_pattern_T, (char*)angle_list, sizeof(float) * max);
	temp_pattern[max] = radius_list[0];
	temp_pattern_T[max] = angle_list[0];

	for (i = 1; i <= max; i++) {
		tmp_angle_diff = fabs(temp_pattern_T[i]  -  temp_pattern_T[i-1]);
		if ( min_angle > temp_pattern_T[i] ) { 
			min_angle = temp_pattern_T[i];
			max_angle_diff = tmp_angle_diff;
			start_idx = i;
		} else if ( min_angle == temp_pattern_T[i] ) {
		       	if ( tmp_angle_diff > max_angle_diff) {
				max_angle_diff = tmp_angle_diff;
				start_idx = i;
			}
		}
	}
	start_idx = start_idx % max;

	printf("DEBUG rearrange_angle_data() : index of start angle = %d\n", start_idx);

	memcpy((char*)radius_list, (char*)&temp_pattern[start_idx], sizeof(float) * (max - start_idx));
	memcpy((char*)&radius_list[max - start_idx], (char*)temp_pattern, sizeof(float) * (start_idx));

	memcpy((char*)angle_list, (char*)&temp_pattern_T[start_idx], sizeof(float) * (max - start_idx));
	memcpy((char*)&angle_list[max - start_idx], (char*)temp_pattern_T, sizeof(float) * (start_idx));

	free(temp_pattern);
	free(temp_pattern_T);
	return 0;
}








#define SAIBI_ABS( x ) ( (x) < 0 ? -(x) : (x))
#define SAIBI_RAD2DEGREE(rad) ( (rad) * 180.0/CONST_PI )
#define SAIBI_DEGREE2RAD(degree) ( (degree) * CONST_PI/180.0)



float polygon_area(float *x_list, float *y_list, int n);
void centroid_of_2point(float *x_list, float *y_list, float *p_cx, float *p_cy);
void centroid_of_polygon(float *x_list, float *y_list, int n, float *p_cx, float *p_cy);


/// N각형 너비 구하는 함수
/// \param x_list
/// \param y_list
/// \param n
/// \return area
float polygon_area(float *x_list, float *y_list, int n)
{
	int i;
	float area = 0.0;

	ASSERT(n >= 3 );

	for (i = 0; i < n-1 ; i ++ ) {
		area += x_list[i] * y_list[i+1];
		area -= y_list[i] * x_list[i+1];
	}
	area += x_list[i] * y_list[0];
	area -= y_list[i] * x_list[0];

	area /= 2;
	return (area < 0 ? -area : area);
}


/// 2점간 무게 중심 구하는 함수
/// \param x_list
/// \param y_list
/// \param p_cx (out)
/// \param p_cy (out)
void centroid_of_2point(float *x_list, float *y_list, float *p_cx, float *p_cy)
{
	float cx = 0.0, cy = 0.0;
	
	if(x_list[0] - x_list[1] > 0) {
		cx=x_list[0] - (SAIBI_ABS(x_list[0]-x_list[1])) / 2;
	}
	else {
		cx=x_list[0] + (SAIBI_ABS(x_list[0]-x_list[1])) / 2;
	}
			
	if(y_list[0] - y_list[1] > 0) {
		cy=y_list[0] - (SAIBI_ABS(y_list[0]-y_list[1])) / 2;
	}
	else {
		cy=y_list[0] + (SAIBI_ABS(y_list[0]-y_list[1])) / 2;
	}
	
	
	if ( p_cx ) {
		*p_cx = cx;
	}
	if ( p_cy ) {
		*p_cy = cy;
	}
}


/// N각형 무게 중심 구하는 함수
/// \param x_list
/// \param y_list
/// \param n
/// \param p_cx (out) center of x
/// \param p_cy (out) center of y 
void centroid_of_polygon(float *x_list, float *y_list, int n, float *p_cx, float *p_cy)
{
	float area;
	float cx = 0.0, cy = 0.0;
	int i;

	ASSERT(n >= 3 );

	area = polygon_area(x_list, y_list, n);

	for (i = 0; i < n - 1 ; i ++ ) {
		cx += (x_list[i] + x_list[i+1]) * ( x_list[i] * y_list[i+1] - x_list[i+1] * y_list[i]);
		cy += (y_list[i] + y_list[i+1]) * ( x_list[i] * y_list[i+1] - x_list[i+1] * y_list[i]);
	}
	cx += (x_list[i] + x_list[0]) * ( x_list[i] * y_list[0] - x_list[0] * y_list[i]);
	cy += (y_list[i] + y_list[0]) * ( x_list[i] * y_list[0] - x_list[0] * y_list[i]);


	if ( p_cx ) {
		*p_cx = cx * 1.0 / (6.0 * area );
	}
	if ( p_cy ) {
		*p_cy = cy * 1.0 / (6.0 * area );
	}
}















/// find box points and boxing center
/// 
///            max y
///       +------------+
///       |  +--------+| max x
///       | /        / |
/// min x ||        /  |
///       | +------+   |
///       +------------+
///         min y
///
/// \param x_list (in)
/// \param y_list (in)
/// \param max
/// \param pminx (out)
/// \param pminy (out)
/// \param pmaxx (out)
/// \param pmaxy (out)
/// \param pcx (out) center x
/// \param pcy (out) center y
static void get_box_points(float *x_list, float *y_list, int max, float *pminx, float *pminy, float *pmaxx, float *pmaxy, float *pcx, float *pcy)
{
	int i;
	float min_x, min_y, max_x, max_y;

	min_x = max_x = x_list[0];
	min_y = max_y = y_list[0];

	for ( i = 1; i < max ; i++ ) {
		if ( x_list[i] < min_x ) {
			min_x = x_list[i];
		} else if ( x_list[i] > max_x ) {
			max_x = x_list[i];
		}

		if ( y_list[i] < min_y ) {
			min_y = y_list[i];
		} else if ( y_list[i] > max_y ) {
			max_y = y_list[i];
		}
	}

	if ( pminx ) {
		*pminx = min_x;
	}
	if ( pminy ) {
		*pminy = min_y;
	}
	if ( pmaxx ) {
		*pmaxx = max_x;
	}
	if ( pmaxy ) {
		*pmaxy = max_y;
	}

	if ( pcx ) {
		*pcx = (min_x + max_x)/2.0;
	}
	if ( pcy ) {
		*pcy = (min_y + max_y)/2.0;
	}
}



int sort_group_member2(void)
{
	int i, j, group_cnt;
	int rand_num;
	float *x_list = NULL;
	float *y_list = NULL;
	float cx, cy;
	float random_x = 0.0;
	float random_y = 0.0;
	int max;
	int ret;
	
	for(i = 0; i < 100; i++) {
		rand_num = (rand() % 4) + 2;
		max = rand_num;
		x_list = (float *)malloc( sizeof(float) * rand_num );
		y_list = (float *)malloc( sizeof(float) * rand_num );
		if ( x_list == NULL ) {
			break;
		}
		if ( y_list == NULL ) {
			sfree(x_list);
			break;
		}
		
		for(j = 0; j < rand_num; j++) {
#if 0			
			while(1) {
				random_x = rand() % 100000;
				random_x = (random_x/1000.0) - 50.0;
				x_list[j] = random_x;
				
				random_y = rand() % 100000;
				random_y = (random_y/1000.0) - 50.0;
				y_list[j] = random_y;
				
				if( sqrt((random_x * random_x) + (random_y * random_y)) >= 16.0) {
					break;
				}
			}
#endif
			x_list[j] = 17.0;
			y_list[j] = 3.0;
		}
#if 0
		printf("\nbefore sort(%d)\n", i);
		for(group_cnt = 0; group_cnt < rand_num ; group_cnt++) {
			printf("x_list[%d] : %f, y_list[%d] : %f\n", group_cnt, x_list[group_cnt], group_cnt, y_list[group_cnt]);
		}
#endif		
		printf("DEBUG 1\n");
		get_box_points(x_list, y_list, max, NULL, NULL, NULL, NULL, &cx, &cy);
		printf("DEBUG 2\n");
		shift_center_xy(x_list, y_list, cx, cy, max);
		printf("DEBUG 3\n");
		if ( (ret = SORT_XY_FRAME_DATA(x_list, y_list, max)) < 0 ) {
			return ret;
		}
		printf("DEBUG 4\n");
		shift_center_xy(x_list, y_list, -cx, -cy, max);
		printf("\nafter sort(%d)\n", i);
		for(group_cnt = 0; group_cnt < rand_num ; group_cnt++) {
			printf("x_list[%d] : %f, y_list[%d] : %f\n", group_cnt, x_list[group_cnt], group_cnt, y_list[group_cnt]);
		}

	}
	
	return 0;
}











#define SORT_XY_FRAME_DATA(x_list, y_list, max) sort_frame_data_core(x_list, y_list, max, SORT_FRAME_DATA_FLAG_XY)

#define MAX_COUNT 7

int main(void)
{
	float x_list[MAX_COUNT] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	float y_list[MAX_COUNT] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	float cx = 0.0, cy = 0.0;
	int i;


	printf("sort test\n");

	printf("before -----------\n");
	for ( i = 0 ; i < MAX_COUNT ; i ++ ) {
		printf("[%d] (%.2f, %.2f)\n", i , x_list[i], y_list[i]);
	}


	SORT_XY_FRAME_DATA(x_list, y_list, MAX_COUNT);


	printf("after -----------\n");
	for ( i = 0 ; i < MAX_COUNT ; i ++ ) {
		printf("[%d] (%.2f, %.2f)\n", i , x_list[i], y_list[i]);
	}


	centroid_of_polygon(x_list, y_list, MAX_COUNT, &cx, &cy);
	printf("center (%.2f, %.2f)\n", cx, cy);

	sort_group_member2();
	return 0;
}

/********** end of file **********/
