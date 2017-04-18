/*!
  \file float.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : ȭ 12 11 18:42:43 KST 2012

*/
#include <stdio.h>


/// tester main
int main(void)
{
	float sensor;
	float compensation;
	double final_value;

	sensor = 1.123;
	compensation = 1.345;

	printf("sensor %.8f, compensation %.8f\n", sensor, compensation);

	if ( sensor == 1.123) 
		printf("sensor ok\n");
	else 
		printf("sensor error\n");

	final_value = sensor + compensation;

	printf("final_value = %.8f\n", final_value);

	if ( final_value == 2.468 ) 
		printf("data ok\n");
	else 
		printf("data error\n");


#if 0
	double lotto = 1.0e10;
	double tax = lotto * 33.0/100.0;
	double result;
	float dvalue = 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1;

	float fvalue1 = 1.345f;
	float fvalue2 = 1.123f;
	float ftotal = fvalue1 + fvalue2;

	result = lotto - tax;
	printf("tax = %f\n", tax);
	printf("result = %f\n", result );

	printf("dvaule = %.17f\n", dvalue);

	printf("ftotal = %.20f\n", ftotal);

	if ( ftotal == 2.468 ) 
		printf("ok\n");
	else 
		printf("error\n");

#endif 
	return 0;
}
/********** end of file **********/
