#include <stdio.h>
#include <math.h>

#define CONST_PI M_PI
#define MAX_RECORD_SIZE 1440


/// 기울기가 theta 인 직선(원점지나는)과 (sy,sx)-(ex,ey) 를 지나는 직전의 교점을 구한다
/// \param theta
/// \param sx
/// \param sy
/// \param ex
/// \param ey
/// \param px (out)
/// \param py (out)
static void get_intersection_point(float theta, float sx, float sy, float ex, float ey, float *px, float *py)
{

	double slope_a;
	double x, y;

	if ( sx == ex ) {
		x = sx;
		y = (sy + ey)/2.0;
	} else if ( theta == CONST_PI/2.0 || theta == CONST_PI * 3.0 / 2.0 ) {
		x = 0.0;
		y = sy - (sy-ey)*sx/(sx-ex);
	} else {
		slope_a = tan(theta);

		if ( slope_a == (sy-ey)/(sx-ex)) {
			x = sx;
			y = (sy + ey)/2.0;
		} else {
			x = ( sy - (sy-ey) * sx/(sx-ex)) / (slope_a - ( (sy-ey)/(sx-ex)));
			y = slope_a * x;
		}
	}

	*px = x;
	*py = y;
}

/// find max angle value and index
/// \param angle_list radian list
/// \param record_count
/// \param p_max (out) max angle  (radian)
/// \return index
static int find_max_angle(float *angle_list, int record_count, float *p_max)
{
	int i;
	float max_angle = 0.0;
	int max_idx = -1;

	for ( i = 0 ; i < record_count; i++ ) {
		if ( angle_list[i] > max_angle ) {
			max_angle = angle_list[i];
			max_idx = i;
		}
	}

	if (p_max ) {
		*p_max = max_angle;
	}
	return max_idx;
}

/// 지정한 각도의 전/후 포인트의 index 얻음
/// \param radius (in) radius data, mm 
/// \param angle (in) angle data, radius
/// \param record_count (in) 
/// \param theta (in) 
/// \param p_start (out) start index
/// \param p_end (out) end index
/// \return 0 success
/// \return -1 error
static int find_neighbor_index(float *radius_list, float *angle_list, int record_count, float theta, int *p_start, int *p_end)
{
	int i, found = 0;
	int prev = 0, cur = 0;
	int max_idx = 0;
	int start_idx = 0;

	static float *prev_r = NULL;
	static float *prev_a = NULL;
	static int prev_max_idx = 0;
	static int prev_start_idx = 0;

	if ( radius_list != NULL && angle_list != NULL ) {
		max_idx = prev_max_idx = find_max_angle(angle_list, record_count, NULL);
		start_idx = 0;
		prev_r = radius_list;
		prev_a = angle_list;
	} else {
		if ( prev_r == NULL || prev_a == NULL ) {
			return -1;
		}

		radius_list = prev_r;
		angle_list = prev_a;
		max_idx = prev_max_idx;
		start_idx = prev_start_idx;
	}

	for ( i = 0 ; i < record_count; i++ ) {
		prev = (start_idx + i - 1 + record_count) % record_count;
		cur = ( start_idx + i + record_count ) % record_count;
		if ( angle_list[prev] <= theta && theta <= angle_list[cur]) {
			found = 1;
			break;
		}
	}
	if (found ) {
		*p_start = prev;
		prev_start_idx = *p_end = cur;
	} else {
		*p_start = max_idx;
		prev_start_idx = *p_end = (max_idx + 1) % record_count;
	}
	return 0;
}

/// 부등각 r/theta 데이터를 등각 r/theta data 로 변환 (아직 제대로 검증은 안해봤는데, excel 로 확인해 보니 그렇저렇 비슷한 형상이 나온다)
///
/// 그리고....이 함수 무쟈게 비 효율적으로 만들었다. 
/// find_neighbor_index() 를 record_count 만큼 호출하는 방식은 개선이 필요하다 
///
/// \param r (in) 부등각 radius
/// \param a (in) 부등각 angle (radian)
/// \param record_count (in) 데이터 갯수  
/// \param target_count (in) 등각 데이터 갯수 
/// \param equi_r (out) 등각 radius
/// \param equi_a (out) 등각 angle
static void make_equiangular_data(float *r, float *a, int record_count, int target_count, float *equi_r, float * equi_a)
{
	float temp_a = 2 * CONST_PI / (target_count);
	int i;
	int start, end;
	float equi_x, equi_y;

	find_neighbor_index(r, a, record_count, 0.0, &start, &end);

	for ( i = 0 ; i < target_count; i++ ) {
		equi_a[i] = temp_a * i;
		find_neighbor_index(NULL, NULL, record_count, equi_a[i], &start, &end);
		if ( start == end ) {
			equi_r[i] = r[i];
		} else {
			get_intersection_point(equi_a[i], r[start] * cos(a[start]), r[start] * sin(a[start]), r[end] * cos( a[end] ), r[end] * sin( a[end] ), &equi_x, &equi_y);

			equi_r[i] = sqrt( equi_x * equi_x + equi_y * equi_y );
		}
	}
}


/// calculate circumference
/// \param x x list
/// \param y y list
/// \param record_count
/// \param length_list (out) length 
/// \return circumference
static float calc_circumference(float *x_list, float *y_list, int record_count, float *length_list)
{
	int i;
	float len;

	if ( record_count < 2 ) {
		return 0.0;
	}

	length_list[0] = 0.0;
	len = 0.0;
	for ( i = 1 ; i < record_count; i++) {
		length_list[i] = sqrt( (x_list[i] - x_list[i-1]) * (x_list[i] - x_list[i-1]) + (y_list[i] -y_list[i-1]) * (y_list[i] - y_list[i-1]) );
		len += length_list[i];
		length_list[i] = len;
	}
	length_list[i] = sqrt( (x_list[0] - x_list[i-1]) * (x_list[0] -x_list[i-1]) + (y_list[0] - y_list[i-1]) * (y_list[0] - y_list[i-1]) );
	len += length_list[i];
	length_list[i] = len;

	return len;
}

/// r theta 좌표 값 을 xy 좌표 값으로 변환 
/// \param x (out)
/// \param y (out)
/// \param r (in)
/// \param a (in)
/// \param record_number
static void convert_r_to_xy(float *x, float *y, float * r, float * a, int record_number)
{
	int i;

	for (i = 0; i < record_number; i++) {
		x[i] = r[i] * sin(a[i]);
		y[i] = r[i] * cos(a[i]);
	}
}

#define POINT_OF_INTERNAL_DIVISION( X1, X2, M, N ) (((M) * (X2) + (N) * (X1)) /((M)+(N)))

/// make  equal length data
/// \param r radius
/// \param a angle(radian)
/// \param record_count
/// \param target_count
/// \param equal_r (out)
/// \param equal_a (out)
static void make_equal_len_data(float *r, float *a, int record_count, int target_count, float *equal_r, float * equal_a)
{
	float x_list[MAX_RECORD_SIZE+1];
	float y_list[MAX_RECORD_SIZE+1];
	float len_list[MAX_RECORD_SIZE+1];
	float cir, equal_len;
	float m, n;
	int i, k;
	float x, y;

	convert_r_to_xy(x_list, y_list, r, a, record_count);

	cir = calc_circumference(x_list, y_list, record_count, len_list);
	equal_len = cir / target_count ;

	equal_r[0] = r[0];
	equal_a[0] = a[0];

	for ( i = 1, k = 1; i < target_count; i++ ) {
		cir = equal_len * i;
		for ( ; k <= record_count; ) {
			if ( cir == len_list[k] ) {
				equal_r[i] = r[k];
				equal_a[i] = a[k];
				k++;
				break;
			} else if ( cir < len_list[k] ) {
				m = cir - len_list[k-1];
				n = len_list[k] - cir;

				x = POINT_OF_INTERNAL_DIVISION( x_list[k-1], x_list[k], m, n);
				y = POINT_OF_INTERNAL_DIVISION( y_list[k-1], y_list[k], m, n);
				equal_r[i] = sqrt( x * x + y * y );
				equal_a[i] = atan2( x, y );
				if ( equal_a[i] < 0.0 ) {
					equal_a[i] += 2 * CONST_PI;
				} 
				break;
			} else {
				k++;
			}
		}
	}
}








// TESTER
int main(void)
{
	extern float sample_frame_radius[MAX_RECORD_SIZE];
	extern float sample_frame_angle[MAX_RECORD_SIZE];

	float r[MAX_RECORD_SIZE];
	float a[MAX_RECORD_SIZE];
	float r2[MAX_RECORD_SIZE];
	float a2[MAX_RECORD_SIZE];
	int i;

	printf("equangular test\n");

	make_equiangular_data(sample_frame_radius, sample_frame_angle, MAX_RECORD_SIZE, MAX_RECORD_SIZE, r, a);
	make_equal_len_data(sample_frame_radius, sample_frame_angle, MAX_RECORD_SIZE, MAX_RECORD_SIZE, r2, a2);

	for( i = 0 ; i < MAX_RECORD_SIZE; i++ ) {
		printf("%d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f\n", i, sample_frame_radius[i], sample_frame_angle[i], r[i], a[i], r2[i], a2[i]);
	}

	return 0;
}

/********** end of file **********/
