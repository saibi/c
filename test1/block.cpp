#include <iostream>
#include <cmath>

using namespace std;

#define CONST_PI_MINUTE M_PI


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

	cout << "gen_block_data() : start\n";

	theta_add = (2 * CONST_PI_MINUTE) / count;
	inflection_theta = acos(height/width);
	pi_m_inflection_theta = CONST_PI_MINUTE - inflection_theta;
	pi_p_inflection_theta = CONST_PI_MINUTE + inflection_theta;
	twopi_m_inflection_theta = 2 * CONST_PI_MINUTE - inflection_theta;

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
	cout << "gen_block_data() : end\n";
}

#define COUNT 144 

int main(void)
{
	float r[COUNT], a[COUNT];
	cout << "test start\n";

	gen_block_data(30, 20, r, a, COUNT);

	for (int i = 0; i < COUNT; i++) {
		cout << r[i] << ", " << a[i] << "\n";
	}

	return 0;
}


