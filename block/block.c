/*!
  \file block.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Thu Dec 01 12:08:58 KST 2011

*/

#include <stdio.h>
#include <math.h>

/// lens adaptor 데이터 생성
/// \param width
/// \param height
/// \param r (out)
/// \param a (out)
/// \param count
static void gen_block_data(float width, float height, float *r, float *a, int count)
{
	float target_theta, inflection_theta, theta_add;
	float pi_m_inflection_theta, pi_p_inflection_theta, twopi_m_inflection_theta;
	int i;

	height /= 2.0;
	width /= 2.0;

	theta_add = (2 * M_PI) / count;
	inflection_theta = acos(height/width);
	pi_m_inflection_theta = M_PI - inflection_theta;
	pi_p_inflection_theta = M_PI + inflection_theta;
	twopi_m_inflection_theta = 2 * M_PI- inflection_theta;

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

#define MAX_COUNT 1440

int main(void)
{
	float r[MAX_COUNT];
	float a[MAX_COUNT];
	int i;

	gen_block_data(34.0, 26.0, r, a, MAX_COUNT);

	for ( i = 0 ; i < MAX_COUNT; i++ ) {
		printf("%.6f,\n", r[i]);
	}

	return 0;
}
/********** end of file **********/
