#include <stdio.h>
#include <math.h>

#define CONST_PI 3.14159

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

/// generate lens adaptor r/a data 
/// \param width cannot be 0.0
/// \param height
/// \param r (out)
/// \param a (out)
/// \param count
static void gen_lens_adaptor_data(float width, float height, float *r, float *a, int count)
{
	float target_theta, inflection_theta, theta_add;
	float pi_m_inflection_theta, pi_p_inflection_theta, twopi_m_inflection_theta;
	int i;

	if ( width == 0.0 ) {
		printf("ASSERT width != 0.0\n");
		return;
	}

	height /= 2.0;
	width /= 2.0;

	theta_add = (2 * CONST_PI) / count;
	inflection_theta = acos(height/width);
	pi_m_inflection_theta = CONST_PI - inflection_theta;
	pi_p_inflection_theta = CONST_PI + inflection_theta;
	twopi_m_inflection_theta = 2 * CONST_PI - inflection_theta;

	for (i = 0, target_theta = 0.0; i < count ; i++, target_theta += theta_add) {
		a[i] = target_theta;
		if ( (target_theta > inflection_theta && target_theta < pi_m_inflection_theta) || (target_theta > pi_p_inflection_theta  && target_theta < twopi_m_inflection_theta)) {
			r[i] = width;
		} else {
			r[i] = height/cos(target_theta);
			if (r[i] < 0.0 ) {
				r[i] *= -1.0;
			}
		}
	}
}


/// generate circle radius / angle
/// \param record_count
/// \param p_radius (out) 
/// \param p_angle (out) 
static void gen_circle(float radius, int record_count, float *p_radius, float *p_angle)
{
	int i = 0;

	for ( i = 0 ; i < record_count; i++ ) 
	{
		p_radius[i] = radius;
		p_angle[i] = i * (2*CONST_PI/record_count); 
	}
}

/// check whether the point is inside the xyframe
/// \param x x list
/// \param y y list
/// \param record_number
/// \param px
/// \param py
/// \param step
/// \return 1 inside
/// \return 0 outside 
static int point_in_xyframe(float *x, float *y, int record_number, float px, float py, int step)
{
	float xnew,ynew;
	float xold,yold;
	float x1,yy1;
	float x2,y2;
	int i;
	int inside=0;

	if ( (record_number < 3) || (step < 1) || (record_number/step < 2) ) {
		return(0);
	}
	xold = x[record_number - (record_number-1) % step -1];
	yold = y[record_number - (record_number-1) % step -1];
	for (i=0 ; i < record_number; i += step) {
		xnew = x[i];
		ynew = y[i];

		if (xnew > xold) {
			x1=xold;
			x2=xnew;
			yy1=yold;
			y2=ynew;
		} else {
			x1=xnew;
			x2=xold;
			yy1=ynew;
			y2=yold;
		}
		if ((xnew < px) == (px <= xold) && (py-yy1)*(x2-x1) < (y2-yy1)*(px-x1)) {
			inside=!inside;
		}
		xold=xnew;
		yold=ynew;
	}
	return(inside);
}

/// calc mm away coords from end point 
static int calc_outer_coords_from_end(float sx, float sy, float ex, float ey, float mm, float *p_out_x, float * p_out_y)
{
	float length;

	length = sqrt( (ex-sx) * (ex-sx) + (ey-sy) * (ey-sy) );

	if ( length == 0.0 ) 
	{
		printf("same point\n");
		return -1;
	}

	*p_out_x = (ex - sx) * ( length + mm ) / length + sx;
	*p_out_y = (ey - sy) * ( length + mm ) / length + sy;

	return 0;
}



#define MAX 100

int main(void)
{
	float r[MAX];
	float a[MAX];
	float x[MAX];
	float y[MAX];
	int i;

	float sx = 27.0;
	float sy = 0.0;
	float ex = 20.0;
	float ey = 4.0;

	float ox, oy;
	int k;


	gen_lens_adaptor_data(50, 30, r, a, MAX);
	gen_circle(25.0, MAX, r, a);
	convert_r_to_xy(x, y, r, a, MAX);

	for (i = 0 ; i < MAX ; i++ )
	{
		printf("#%d (%.2f, %.2f) -> (%.2f, %.2f)\n", i, r[i], a[i], x[i], y[i]);
	}

	for ( k = 0 ; k < 1; k++ ) 
	{
		printf("#%d (%.2f, %.2f) ~ (%.2f, %.2f) \n", k, sx, sy, ex, ey);

		if ( point_in_xyframe( x, y, MAX, sx, sy, 1) == 0 )
		{
			calc_outer_coords_from_end( ex, ey, sx, sy, 2.0, &ox, &oy);
			printf("start point out (%.2f, %.2f)\n", ox, oy);

		}
		if ( point_in_xyframe( x, y, MAX, ex, ey, 1) == 0 )
		{
			calc_outer_coords_from_end( sx, sy, ex, ey, 2.0, &ox, &oy);
			printf("end point out (%.2f, %.2f)\n", ox, oy);
		}
	}
	return 0;
}

