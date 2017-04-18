#ifndef _ALGO_H_
#define _ALGO_H_

#define	INT_SCALE		512

#define SQRT_MIN		(0*INT_SCALE)
#define SQRT_MAX		(130*INT_SCALE)

double CalculatingDeterminantOf2by2Matrix(double TZZ[3][3], int rowi, int rowj, int columnk, int columnl);
double calculating_radius_Fn(double x[], double y[], double z[]);
void Calculatingdistance(double x[],double y[],double z[],double distance[]);
int my_sqrt(int in);
int filter_float_data(float *target, float *src, int array_size, int param_window_size);
float calcCurvature(float x[], float y[], int idx);
#endif
