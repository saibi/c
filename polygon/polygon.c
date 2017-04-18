#include <stdio.h>
#include <math.h>

#define MAX_RECORD_SIZE 1440

#include "x.c"

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

/// xy 좌표 값을 r theta 좌표 값으로 변환 
/// \param r (out)
/// \param a (out)
/// \param x (in)
/// \param y (in)
/// \param record_number
static void convert_xy_to_r(float *r, float *a, float *x, float *y, int record_number)
{
	int i;

	for ( i = 0 ; i <record_number; i++) {
		r[i] = sqrt( (x[i] * x[i]) + (y[i] * y[i]));

		a[i] = atan2(x[i], y[i]);
		if ( a[i] < 0.0 ) {
			a[i] += 2 * M_PI;
		}
	}
}

/// 중심이동 (xy 좌표)
/// \param x (out)
/// \param y (out)
/// \param delta_x
/// \param delta_y
/// \param record_number
static void shift_center_xy(float *x, float *y, float delta_x, float delta_y, int record_number)
{
	int i;

	for (i = 0 ; i < record_number; i++) {
		x[i] -= delta_x;
		y[i] -= delta_y;
	}
}

/// calculate center coords & width/height
/// \param x_list 
/// \param y_list
/// \param record_count
/// \param p_cx (out)
/// \param p_cy (out)
/// \param p_width (out)
/// \param p_height (out)
/// \return 0 success
static int calc_polygon_center_width_height(float *x_list, float *y_list, int record_count, float *p_cx, float *p_cy, float *p_width, float *p_height)
{
	int i;
	float min_x, min_y, max_x, max_y;

	if ( x_list == NULL || y_list == NULL || record_count < 3 ) {
		return -1;
	}

	min_x = max_x = x_list[0];
	min_y = max_y = y_list[0];

	for ( i = 1 ; i < record_count; i++ ) {
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

	if ( p_cx ) {
		*p_cx = (max_x + min_x) / 2.0;
	}
	if ( p_cy ) {
		*p_cy = (max_y + min_y) / 2.0;
	}
	if ( p_width ) {
		*p_width = fabs(max_x - min_x);
	}
	if ( p_height ) {
		*p_height = fabs(max_y - min_y);
	}
	return 0;
}



/// zoom polygon 
/// IMPORTANT : center coords of the polygon must be (0.0, 0.0)
///             if the center is not in (0.0, 0.), use shift_center_xy(float *x, float *y, float delta_x, float delta_y, int record_number)
/// \param x_list (in/out)
/// \param y_list (in/out)
/// \param record_count
/// \param width
/// \param height 
/// \param delta_x 
/// \param delta_y
/// \return 0 success
static int zoom_polygon_xy(float *x_list, float *y_list, int record_count, float width, float height, float delta_x, float delta_y)
{
	int i;
	float val_x, val_y;

	if ( x_list == NULL || y_list == NULL || record_count < 3 || width == 0.0 || height == 0.0 ) {
		return -1;
	}
	val_x = (width + delta_x) / width;
	val_y = (height + delta_y) / height;

	if ( delta_x != 0.0 && delta_y != 0.0 ) {
		for (i = 0; i < record_count; i++) {
			x_list[i] *= val_x;
			y_list[i] *= val_y;
		}
	} else if ( delta_x != 0.0 ) {
		for (i = 0; i < record_count; i++) {
			x_list[i] *= val_x;
		}
	} else {
		for (i = 0; i < record_count; i++) {
			y_list[i] *= val_y;
		}
	}
	return 0;
}



int main(int argc, char *argv[])
{

	int i;
	float cx, cy, width, height;
	int ret;

	shift_center_xy(x_list, y_list, -10.4, 3.2, MAX_RECORD_SIZE);

	ret = calc_polygon_center_width_height(x_list, y_list, MAX_RECORD_SIZE, &cx, &cy, &width, &height);
	printf("ret = %d\n", ret);

	zoom_polygon_xy(x_list, y_list, MAX_RECORD_SIZE, width, height, -5.0, -5.0);

	printf("float x_list[] = { \n");
	for ( i = 0 ; i < MAX_RECORD_SIZE; i++) {
		printf("%.2f\n", x_list[i]);
	}

	printf("\n\nfloat y_list[] = { \n");
	for ( i = 0 ; i < MAX_RECORD_SIZE; i++) {
		printf("%.2f\n", y_list[i]);
	}

#if 0
	convert_r_to_xy(x_list, y_list, r_list, a_list, MAX_RECORD_SIZE);

	printf("x_list[] = \n");
	for ( i = 0 ; i < MAX_RECORD_SIZE; i++ ) {
		printf("%.2f, ", x_list[i]);
		if ( ( (i+1) % 32 ) == 0 ) {
			printf("\n");
		}
	}

	printf("\n\ny_list[] = \n");
	for ( i = 0 ; i < MAX_RECORD_SIZE; i++ ) {
		printf("%.2f, ", y_list[i]);
		if ( ( (i+1) % 32 ) == 0 ) {
			printf("\n");
		}
	}



	float x_list[MAX_RECORD_SIZE];
	float y_list[MAX_RECORD_SIZE];
	printf("before zoom\n");
	for ( i = 0 ; i < 4; i++ ) {
		printf("(%.2f, %.2f) , (%.2f, %.2f)\n", x_list[i], y_list[i], x2_list[i], y2_list[i]);
	}

	zoom_polygon_xy(x_list, y_list, 4, 4, 4, 10, 2 );
	zoom_polygon_xy(x2_list, y2_list, 4, 4, 4, 10, 2 );

	printf("after zoom\n");
	for ( i = 0 ; i < 4; i++ ) {
		printf("(%.2f, %.2f) , (%.2f, %.2f)\n", x_list[i], y_list[i], x2_list[i], y2_list[i]);
	}

#endif 
	return 0;
}
/********** end of file **********/
