#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define TRUE 1
#define FALSE 0

#if 0
int case1(void)
{
	int bSortTable = TRUE;
	float center_diff_x;
	int m_bReferenceSortingOrder;

	printf("precedency test\n");

	center_diff_x = 1.0;
	m_bReferenceSortingOrder = TRUE;

	printf("center_diff_x = %f, m_bReferenceSortingOrder = %d\n", center_diff_x, m_bReferenceSortingOrder);
	if (bSortTable && ( (center_diff_x > 0.f && m_bReferenceSortingOrder == TRUE) || (center_diff_x <= 0.f && m_bReferenceSortingOrder == FALSE)))
		printf("true\n");
	else
		printf("false\n");

	center_diff_x = -1.0;
	m_bReferenceSortingOrder = FALSE;

	printf("center_diff_x = %f, m_bReferenceSortingOrder = %d\n", center_diff_x, m_bReferenceSortingOrder);
	if (bSortTable && (center_diff_x > 0.f && m_bReferenceSortingOrder == TRUE || center_diff_x <= 0.f && m_bReferenceSortingOrder == FALSE))
		printf("true\n");
	else
		printf("false\n");


	center_diff_x = 1.0;
	m_bReferenceSortingOrder = FALSE;

	printf("center_diff_x = %f, m_bReferenceSortingOrder = %d\n", center_diff_x, m_bReferenceSortingOrder);
	if (bSortTable && (center_diff_x > 0.f && m_bReferenceSortingOrder == TRUE || center_diff_x <= 0.f && m_bReferenceSortingOrder == FALSE))
		printf("true\n");
	else
		printf("false\n");

	center_diff_x = -1.0;
	m_bReferenceSortingOrder = TRUE;

	printf("center_diff_x = %f, m_bReferenceSortingOrder = %d\n", center_diff_x, m_bReferenceSortingOrder);
	if (bSortTable && (center_diff_x > 0.f && m_bReferenceSortingOrder == TRUE || center_diff_x <= 0.f && m_bReferenceSortingOrder == FALSE))
		printf("true\n");
	else
		printf("false\n");

	return 0;
}
#endif 

void case2(void)
{
	int b_base_Hawaii;
	int frameData_isHawaii;
	int s_retouch_edging_points_size;
	int b_modify_impossible_points;

	b_base_Hawaii = TRUE;
	frameData_isHawaii = TRUE;
	s_retouch_edging_points_size = 10;
	b_modify_impossible_points = TRUE;

	printf("b_base_Hawaii = %d, frameData_isHawaii = %d, s_retouch_edging_points_size = %d, b_modify_impossible_points = %d\n", b_base_Hawaii, frameData_isHawaii, s_retouch_edging_points_size, b_modify_impossible_points);
	if ( b_base_Hawaii && frameData_isHawaii && s_retouch_edging_points_size > 0 || b_modify_impossible_points) 
		printf("true\n");
	else
		printf("false\n");


	b_base_Hawaii = FALSE;
	frameData_isHawaii = FALSE;
	s_retouch_edging_points_size = 0;
	b_modify_impossible_points = TRUE;

	printf("b_base_Hawaii = %d, frameData_isHawaii = %d, s_retouch_edging_points_size = %d, b_modify_impossible_points = %d\n", b_base_Hawaii, frameData_isHawaii, s_retouch_edging_points_size, b_modify_impossible_points);
	if ( b_base_Hawaii && frameData_isHawaii && s_retouch_edging_points_size > 0 || b_modify_impossible_points) 
		printf("true\n");
	else
		printf("false\n");

}

	
int main(void)
{
	int a, b, c;

	a = 1;
	b = 0; 
	c = 0;

	if ( a || b && c ) 
		printf("1\n");
	else
		printf("0\n");

	if ( (a || b) && c ) 
		printf("1\n");
	else
		printf("0\n");

	//case1();
	//case2();


	return 0;
}


