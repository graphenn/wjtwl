#include <stdio.h>
#include <stdlib.h>
#include "wjtwl_lib.h"

const int8_t month_max[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


/*公历儒略日互转*/
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

	/* 1582年10月15日0时0分0秒的儒略日为198647467200 */
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
本函数实现儒略日转格里高利历和儒略历。calendar_type等于0表示儒略历，1表示格里高利历。
参数检查在上层函数做。算法参考：
https://en.wikipedia.org/wiki/Julian_day
*/
void julian_day_2_julian_gregorian_calendar(jd_t julian_day, int calendar_type, wjtwl_date_t *julian_gregorian_calendar)
{
	int_fast32_t e, h;
	int_fast16_t time;

	/*
	为支持到公元前10000年，需要拓展Julian Day基准日期，提前到公元前10000年以前。
	儒略日循环为1461天，因此选择提前1931442天，166876588800秒。
	此时基准日期为公元前10001年1月1日。
	同时添加儒略日12小时时间及时区补正43200，共166876632000秒。
	*/
	julian_day += 166876632000 + g_time_zone;

	/*
	求日期，取日数， julian_day / 24 / 60 / 60
	及取余数，用作算时、分、秒
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
	因修改了基准日期。岁差一共 100000 / 400 * 3 + 2 = 77年
	基准日期的格里历为公元前10002年10月16日，到公元前10001年3月1日共136天
	146097 - ( 136 * 4) = 145553。
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
	修改基准日期后，需要比公式多减5288年。
	*/
	julian_gregorian_calendar->year = (int16_t)((e / 1461) - 10004 + ((14 - julian_gregorian_calendar->month) / 12));

	/* 再求时分秒 */
	julian_gregorian_calendar->hour = (int8_t)(time / 3600);
	julian_gregorian_calendar->minute = (int8_t)((time % 3600) / 60);
	julian_gregorian_calendar->second = (int8_t)(time % 60);

	return;
}


/*
格里高利历儒略日互转，算法参考：
https://en.wikipedia.org/wiki/Julian_day
*/
int gregorian_calendar_2_julian_day(wjtwl_date_t gregorian_calendar, jd_t *julian_day)
{
	int m;
	jd_t julian_day_temp;

	/* 儒略历公元前10000年1月1日时，格里历已经到公元前10001年，因时区影响，可能到4001年 */
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
	如下算法仅支持JDN>=0。为支持到公元前10000年，需要换算年份至-4713-11-23以后。
	格里历循环为146097天，400年。因此选择年份增加5600年，2045358天，176718931200秒。
	此时-10313-11-23换算为-4713-11-23。
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

	/* 换算年份及时区补正及儒略日12小时（43200秒）补正 */
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
儒略历儒略日互转，算法参考：
https://en.wikipedia.org/wiki/Julian_day
*/
int julian_calendar_2_julian_day(wjtwl_date_t julian_calendar, jd_t *julian_day)
{
	jd_t julian_day_temp;

	/* 经时区修正后，可能会到公元前10001年 */
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
	如下算法仅支持JDN>=0。为支持到公元前10000年，需要换算年份至-4712年以后。
	儒略历循环为1461天，因此选择年份增加5288年，1931442天，166876588800秒。
	此时公元前10001年1月1日换算为公元前4713年1月1日。
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

	/* 换算年份及时区补正及儒略日12小时（43200秒）补正 */
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