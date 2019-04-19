#include <stdio.h>
#include <stdlib.h>
#include "wjtwl_lib.h"

#define DIFF_JULIAN_DAY_MODIFIED_JULIAN_DAY (207360043200)

/*����������Ϊ��λ������Ϊ��λ��ת��ͬʱ֧�ּ�������*/
int julian_day_2_julian_day_day(jd_t julian_day, double *julian_day_day)
{
	*julian_day_day = (double)julian_day / 86400;

	return WJTWL_SUCCESS;
}

int julian_day_day_2_julian_day(double julian_day_day, jd_t *julian_day)
{
	*julian_day = (jd_t)(julian_day_day * 86400);

	return WJTWL_SUCCESS;
}

/*�������������ջ�ת*/
int modified_julian_day_2_julian_day(jd_t modified_julian_day, jd_t *julian_day)
{
	if ((modified_julian_day < (JULIAN_DAY_MIN - DIFF_JULIAN_DAY_MODIFIED_JULIAN_DAY)) || (modified_julian_day > (JULIAN_DAY_MAX - DIFF_JULIAN_DAY_MODIFIED_JULIAN_DAY)))
	{
		return WJTWL_ERROR_DATE;
	}

	*julian_day = modified_julian_day + DIFF_JULIAN_DAY_MODIFIED_JULIAN_DAY;

	return WJTWL_SUCCESS;
}

int julian_day_2_modified_julian_day(jd_t julian_day, jd_t *modified_julian_day)
{
	check_jd(julian_day);

	*modified_julian_day = julian_day - DIFF_JULIAN_DAY_MODIFIED_JULIAN_DAY;

	return WJTWL_SUCCESS;
}
