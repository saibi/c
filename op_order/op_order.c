#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define TRUE 1
#define FALSE 0

int main(void)
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
	
