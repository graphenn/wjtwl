#include <stdio.h>
#include <stdlib.h>
#include "wjtwl_lib.h"

const int8_t month_max[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


/*���������ջ�ת*/
int calendar_2_julian_day(wjtwl_date_t calendar, jd_t *julian_day)
{
	int ret, calendar_type;

	if (calendar.year > 1582)
	{
		calendar_type = 1;
	}
	else if (calendar.year < 1582)
	{
		calendar_type = 0;
	}
	else
	{
		if (calendar.month > 10)
		{
			calendar_type = 1;
		}
		else if (calendar.month < 10)
		{
			calendar_type = 0;
		}
		else
		{
			if (calendar.day >= 15)
			{
				calendar_type = 1;
			}
			else if (calendar.day <= 4)
			{
				calendar_type = 0;
			}
			else
			{
				return WJTWL_ERROR_DATE;
			}
		}
	}

	if (calendar_type)
	{
		ret = gregorian_calendar_2_julian_day(calendar, julian_day);
	}
	else
	{
		ret = julian_calendar_2_julian_day(calendar, julian_day);
	}

	return ret;
}

int julian_day_2_calendar(jd_t julian_day, wjtwl_date_t *calendar)
{
	check_jd(julian_day);

	/* 1582��10��15��0ʱ0��0���������Ϊ198647467200 */
	if ((julian_day + g_time_zone) >= 198647467200)
	{
		julian_day_2_gregorian_calendar(julian_day, calendar);
	}
	else
	{
		julian_day_2_julian_calendar(julian_day, calendar);
	}

	return WJTWL_SUCCESS;
}

/*
������ʵ��������ת�������������������calendar_type����0��ʾ��������1��ʾ�����������
����������ϲ㺯�������㷨�ο���
https://en.wikipedia.org/wiki/Julian_day
*/
void julian_day_2_julian_gregorian_calendar(jd_t julian_day, int calendar_type, wjtwl_date_t *julian_gregorian_calendar)
{
	int_fast32_t e, h;
	int_fast16_t time;

	/*
	Ϊ֧�ֵ���Ԫǰ10000�꣬��Ҫ��չJulian Day��׼���ڣ���ǰ����Ԫǰ10000����ǰ��
	������ѭ��Ϊ1461�죬���ѡ����ǰ1931442�죬166876588800�롣
	��ʱ��׼����Ϊ��Ԫǰ10001��1��1�ա�
	ͬʱ���������12Сʱʱ�估ʱ������43200����166876632000�롣
	*/
	julian_day += 166876632000 + g_time_zone;

	/*
	�����ڣ�ȡ������ julian_day / 24 / 60 / 60
	��ȡ������������ʱ���֡���
	*/
	e = (int_fast32_t)(julian_day / 86400);
	time = (int_fast16_t)(julian_day - ((jd_t)e * 86400));

	julian_gregorian_calendar->weak = (int8_t)(((e + 5) % 7) + 1);

	/*
	y   4716    v   3
	j   1401    u   5
	m   2       s   153
	n   12      w   2
	r   4       B   274277
	p   1461    C   -38
	*/

	/*
	Julian calendar
	1. f = J + j
	Gregorian calendar
	1. f = J + j + (((4 * J + B) div 146097) * 3) div 4 + C
	���޸��˻�׼���ڡ����һ�� 100000 / 400 * 3 + 2 = 77��
	��׼���ڵĸ�����Ϊ��Ԫǰ10002��10��16�գ�����Ԫǰ10001��3��1�չ�136��
	146097 - ( 136 * 4) = 145553��
	*/

	if (calendar_type)
	{
		e += 1401 + ((((e << 2) + 145553) / 146097) * 3) / 4 - 77;
	}
	else
	{
		e += 1401;
	}

	/* 2. e = r * f + v */
	e = (e << 2) + 3;

	/* 3. g = mod(e, p) div r */
	h = (e % 1461) >> 2;

	/*
	4. h = u * g + w
	*/
	h = h * 5 + 2;

	/* 5. D = (mod(h, s)) div u + 1 */
	julian_gregorian_calendar->day = (int8_t)((h % 153) / 5 + 1);

	/* 6. M = mod(h div s + m, n) + 1 */
	julian_gregorian_calendar->month = (int8_t)(((h / 153 + 2) % 12) + 1);

	/*
	7. Y = (e div p) - y + (n + m - M) div n
	�޸Ļ�׼���ں���Ҫ�ȹ�ʽ���5288�ꡣ
	*/
	julian_gregorian_calendar->year = (int16_t)((e / 1461) - 10004 + ((14 - julian_gregorian_calendar->month) / 12));

	/* ����ʱ���� */
	julian_gregorian_calendar->hour = (int8_t)(time / 3600);
	julian_gregorian_calendar->minute = (int8_t)((time % 3600) / 60);
	julian_gregorian_calendar->second = (int8_t)(time % 60);

	return;
}


/*
��������������ջ�ת���㷨�ο���
https://en.wikipedia.org/wiki/Julian_day
*/
int gregorian_calendar_2_julian_day(wjtwl_date_t gregorian_calendar, jd_t *julian_day)
{
	int m;
	jd_t julian_day_temp;

	/* ��������Ԫǰ10000��1��1��ʱ���������Ѿ�����Ԫǰ10001�꣬��ʱ��Ӱ�죬���ܵ�4001�� */
	if ((gregorian_calendar.year < -10000) || (gregorian_calendar.year > 4001) || (gregorian_calendar.month < 1) || (gregorian_calendar.month > 12) || (gregorian_calendar.day < 1)
		|| (gregorian_calendar.hour < -1) || (gregorian_calendar.hour > 23) || (gregorian_calendar.minute < -1) || (gregorian_calendar.minute > 59)
		|| (gregorian_calendar.second < -1) || (gregorian_calendar.second > 59))
	{
		return WJTWL_ERROR_DATE;
	}

	if ((gregorian_calendar.day > month_max[gregorian_calendar.month]) && !((2 == gregorian_calendar.month) && (29 == gregorian_calendar.day) && (0 == (gregorian_calendar.year % 4))
		&& ((0 == (gregorian_calendar.year % 400)) || !((0 == (gregorian_calendar.year % 100)) && (0 != (gregorian_calendar.year % 400))))))
	{
		return WJTWL_ERROR_DATE;
	}

	/*
	�����㷨��֧��JDN>=0��Ϊ֧�ֵ���Ԫǰ10000�꣬��Ҫ���������-4713-11-23�Ժ�
	������ѭ��Ϊ146097�죬400�ꡣ���ѡ���������5600�꣬2045358�죬176718931200�롣
	��ʱ-10313-11-23����Ϊ-4713-11-23��
	*/
	gregorian_calendar.year += 5600;

	m = (gregorian_calendar.month - 14) / 12;
	julian_day_temp = (jd_t)((1461 * (gregorian_calendar.year + 4800 + m)) / 4 + (367 * (gregorian_calendar.month - 2 - 12 * m)) / 12
		- (3 * ((gregorian_calendar.year + 4900 + m) / 100)) / 4 + gregorian_calendar.day - 32075) * 86400;

	if (gregorian_calendar.hour > -1)
	{
		julian_day_temp += gregorian_calendar.hour * 3600;

		if (gregorian_calendar.minute > -1)
		{
			julian_day_temp += gregorian_calendar.minute * 60;

			if (gregorian_calendar.second > -1)
			{
				julian_day_temp += gregorian_calendar.second;
			}
		}
	}

	/* ������ݼ�ʱ��������������12Сʱ��43200�룩���� */
	julian_day_temp = julian_day_temp - 176718974400 - g_time_zone;

	check_jd(julian_day_temp);

	*julian_day = julian_day_temp;

	return WJTWL_SUCCESS;
}

int julian_day_2_gregorian_calendar(jd_t julian_day, wjtwl_date_t *gregorian_calendar)
{
	check_jd(julian_day);

	julian_day_2_julian_gregorian_calendar(julian_day, 1, gregorian_calendar);

	return WJTWL_SUCCESS;
}


/*
�����������ջ�ת���㷨�ο���
https://en.wikipedia.org/wiki/Julian_day
*/
int julian_calendar_2_julian_day(wjtwl_date_t julian_calendar, jd_t *julian_day)
{
	jd_t julian_day_temp;

	/* ��ʱ�������󣬿��ܻᵽ��Ԫǰ10001�� */
	if ((julian_calendar.year < -10000) || (julian_calendar.year > 4000) || (julian_calendar.month < 1) || (julian_calendar.month > 12) || (julian_calendar.day < 1) 
		|| (julian_calendar.hour < -1) || (julian_calendar.hour > 23) || (julian_calendar.minute < -1) || (julian_calendar.minute > 59) 
		|| (julian_calendar.second < -1) || (julian_calendar.second > 59))
	{
		return WJTWL_ERROR_DATE;
	}

	if ((julian_calendar.day > month_max[julian_calendar.month]) && !((2 == julian_calendar.month) && (29 == julian_calendar.day) && (0 == (julian_calendar.year % 4))))
	{
		return WJTWL_ERROR_DATE;
	}

	/*
	�����㷨��֧��JDN>=0��Ϊ֧�ֵ���Ԫǰ10000�꣬��Ҫ���������-4712���Ժ�
	������ѭ��Ϊ1461�죬���ѡ���������5288�꣬1931442�죬166876588800�롣
	��ʱ��Ԫǰ10001��1��1�ջ���Ϊ��Ԫǰ4713��1��1�ա�
	*/
	julian_calendar.year += 5288;

	julian_day_temp = (jd_t)(367 * julian_calendar.year - (7 *(julian_calendar.year + 5001 + (julian_calendar.month - 9) / 7))
		/ 4 + (275 * julian_calendar.month) / 9 + julian_calendar.day + 1729777) * 86400;

	if (julian_calendar.hour > -1)
	{
		julian_day_temp += julian_calendar.hour * 3600;

		if (julian_calendar.minute > -1)
		{
			julian_day_temp += julian_calendar.minute * 60;

			if (julian_calendar.second > -1)
			{
				julian_day_temp += julian_calendar.second;
			}
		}
	}

	/* ������ݼ�ʱ��������������12Сʱ��43200�룩���� */
	julian_day_temp = julian_day_temp - 166876632000 - g_time_zone;
	
	check_jd(julian_day_temp);

	*julian_day = julian_day_temp;

	return WJTWL_SUCCESS;
}

int julian_day_2_julian_calendar(jd_t julian_day, wjtwl_date_t *julian_calendar)
{
	check_jd(julian_day);

	julian_day_2_julian_gregorian_calendar(julian_day, 0, julian_calendar);

	return WJTWL_SUCCESS;
}