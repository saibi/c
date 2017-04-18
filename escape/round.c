#include <stdio.h>
#include <math.h>


// rounds a double variable to nPlaces decimal places
float excel_round(float dbVal, int nPlaces /* = 0 */)
{
    float dbShift = pow(10.0, nPlaces);
    return  floor(dbVal * dbShift + 0.5002) / dbShift; 
}   

int main(void)
{
	float a = 3.141592;

	printf("a = %f\n", excel_round(a, 2));
	return 0;
}

