#include <stdio.h>
#include <stdlib.h>
#include "wjtwl.h"


/*�����գ��������ջ�ת������������Ϊ��λ������Ϊ��λ��ת*/
#define TEST_1 (0)
/*���û�ȡʱ��*/
#define TEST_2 (1)
/*������ת��������������������*/
#define TEST_3 (0)
/*��������������������ת������*/
#define TEST_4 (1)
/*�������������ջ�ת��Ĭ����*/
#define TEST_5 (0)
/*����������������ջ�ת��Ĭ����*/
#define TEST_6 (0)

int main()
{
	int ret;

#if TEST_1 
	jd_t modified_julian_day, julian_day;
	double julian_day_day;

	julian_day_day = 2444147.5;
	//julian_day_day = 0;
	//julian_day_day = -0.1;

	ret = julian_day_day_2_julian_day(julian_day_day, &julian_day);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in julian_day_day_2_julian_day with error numer %d\n", ret);
	}
	else
	{
		printf("Julian Day is %lld\n", julian_day);
	}

	ret = julian_day_2_modified_julian_day(julian_day, &modified_julian_day);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in julian_day_2_modified_julian_day with error numer %d\n", ret);
	}
	else
	{
		printf("MJD is %lld\n", modified_julian_day);
	}

	ret = julian_day_2_julian_day_day(modified_julian_day, &julian_day_day);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in julian_day_2_julian_day_day with error numer %d\n", ret);
	}
	else
	{
		printf("MJD is %f\n", julian_day_day);
	}

	ret = modified_julian_day_2_julian_day(modified_julian_day, &julian_day);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in modified_julian_day_2_julian_day with error numer %d\n", ret);
	}
	else
	{
		printf("JD is %lld\n", julian_day);
	}

	ret = julian_day_2_julian_day_day(julian_day, &julian_day_day);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in julian_day_2_julian_day_day with error numer %d\n", ret);
	}
	else
	{
		printf("JD day day is %f\n", julian_day_day);
	}
	

#endif // TEST_1

#if TEST_2
	wjtwl_config_t wjtwl_config;

	ret = wjtwl_get_config(&wjtwl_config);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in wjtwl_get_config with error numer %d\n", ret);
	}
	else
	{
		printf("Time zone is %f\n", wjtwl_config.time_zone);
	}

	//wjtwl_config.time_zone = 0;
	wjtwl_config.time_zone = 14;
	//wjtwl_config.time_zone = -12;
	ret = wjtwl_set_config(&wjtwl_config);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in wjtwl_get_config with error numer %d\n", ret);
	}

	ret = wjtwl_get_config(&wjtwl_config);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in wjtwl_get_config with error numer %d\n", ret);
	}
	else
	{
		printf("Time zone is %f\n", wjtwl_config.time_zone);
	}


#endif // TEST_2

#if TEST_3
	jd_t julian_day;
	double julian_day_day;
	wjtwl_date_t date;

	/* 2000�� 1�� 1.5�� */
	//julian_day_day = 2451545;

	/* 
	������12:00 November 24, 4714 BC
	������12:00 Monday, January 1, 4713 BC
	*/
	//julian_day_day = 0;

	//julian_day_day = 0.5;
	//julian_day_day = -1;
	//julian_day_day = -0.5;
	//julian_day_day = -0.1;
	//julian_day_day = 2455987;

	/* 1582��10��15�� */
	//julian_day_day = 2299160.5;

	/* ��Ԫǰ10000��1��1��0ʱ0��0�� */
	julian_day_day = -1931076.499;
	julian_day = 274959014399;
	ret = julian_day_2_julian_day_day(julian_day, &julian_day_day);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in julian_day_2_julian_day_day with error numer %d\n", ret);
	}
	else
	{
		printf("julian day day is %f\n", julian_day_day);
	}

	ret = julian_day_day_2_julian_day(julian_day_day, &julian_day);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in julian_day_day_2_julian_day with error numer %d\n", ret);
	}
	else
	{
		printf("Julian Day is %lld\n", julian_day);
	}

	ret = julian_day_2_gregorian_calendar(julian_day, &date);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in julian_day_2_gregorian_calendar with error numer %d\n", ret);
	}
	else
	{
		printf("Gregorian Calendar: Year:%d, Month:%d, Day:%d, Hour:%d, Minute:%d, Second:%d, Weak:%d\n", date.year, date.month, date.day, date.hour, date.minute, date.second, date.weak);
	}

	ret = julian_day_2_julian_calendar(julian_day, &date);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in julian_day_2_julian_calendar with error numer %d\n", ret);
	}
	else
	{
		printf("Julian Calendar: Year:%d, Month:%d, Day:%d, Hour:%d, Minute:%d, Second:%d, Weak:%d\n", date.year, date.month, date.day, date.hour, date.minute, date.second, date.weak);
	}

	ret = julian_calendar_2_julian_day(date, &julian_day);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in julian_calendar_2_julian_day with error numer %d\n", ret);
	}
	else
	{
		printf("Julian Calendar Julian day is %lld\n", julian_day);
	}

	ret = julian_day_2_calendar(julian_day, &date);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in julian_day_2_calendar with error numer %d\n", ret);
	}
	else
	{
		printf("Calendar: Year:%d, Month:%d, Day:%d, Hour:%d, Minute:%d, Second:%d, Weak:%d\n", date.year, date.month, date.day, date.hour, date.minute, date.second, date.weak);
	}

#endif // TEST_3

#if TEST_4
	jd_t julian_day;
	wjtwl_date_t date, date_origin;
	
	/*
	date_origin.year = 4000;
	date_origin.month = 12;
	date_origin.day = 31;
	date_origin.hour = 23;
	date_origin.minute = 59;
	date_origin.second = 59;
	date_origin.weak = -1;
	*/

	
	date_origin.year = 1582;
	date_origin.month = 10;
	date_origin.day = 5;
	date_origin.hour = 0;
	date_origin.minute = 0;
	date_origin.second = 0;
	date_origin.weak = -1;
	

	/*
	date_origin.year = -9999;
	date_origin.month = 1;
	date_origin.day = 1;
	date_origin.hour = 0;
	date_origin.minute = 0;
	date_origin.second = 0;
	date_origin.weak = -1;
	*/

	/*
	date_origin.year = -24;
	date_origin.month = 4;
	date_origin.day = 30;
	date_origin.hour = 13;
	date_origin.minute = 29;
	date_origin.second = 23;
	date_origin.weak = -1;
	*/

	julian_day = 0;

	ret = calendar_2_julian_day(date_origin, &julian_day);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in calendar_2_julian_day with error numer %d\n", ret);
	}
	else
	{
		printf("Calendar Julian day is %lld\n", julian_day);
	}

	ret = julian_day_2_calendar(julian_day, &date);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in julian_day_2_calendar with error numer %d\n", ret);
	}
	else
	{
		printf("Calendar: Year:%d, Month:%d, Day:%d, Hour:%d, Minute:%d, Second:%d, Weak:%d\n", date.year, date.month, date.day, date.hour, date.minute, date.second, date.weak);
	}

	ret = julian_calendar_2_julian_day(date_origin, &julian_day);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in julian_calendar_2_julian_day with error numer %d\n", ret);
	}
	else
	{
		printf("Julian Calendar Julian day is %lld\n", julian_day);
	}

	ret = julian_day_2_julian_calendar(julian_day, &date);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in julian_day_2_julian_calendar with error numer %d\n", ret);
	}
	else
	{
		printf("Julian Calendar: Year:%d, Month:%d, Day:%d, Hour:%d, Minute:%d, Second:%d, Weak:%d\n", date.year, date.month, date.day, date.hour, date.minute, date.second, date.weak);
	}

	ret = gregorian_calendar_2_julian_day(date_origin, &julian_day);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in gregorian_calendar_2_julian_day with error numer %d\n", ret);
	}
	else
	{
		printf("Gregorian Calendar Julian day is %lld\n", julian_day);
	}

	ret = julian_day_2_gregorian_calendar(julian_day, &date);
	if (WJTWL_SUCCESS != ret)
	{
		printf("something wrong in julian_day_2_gregorian_calendar with error numer %d\n", ret);
	}
	else
	{
		printf("Gregorian Calendar: Year:%d, Month:%d, Day:%d, Hour:%d, Minute:%d, Second:%d, Weak:%d\n", date.year, date.month, date.day, date.hour, date.minute, date.second, date.weak);
	}

#endif // TEST_4

#if TEST_5
	jd_t julian_day, julian_day_origin;
	wjtwl_date_t date;
	for (julian_day = 198648374400; julian_day <= JULIAN_DAY_MAX; julian_day++)
	{
		julian_day_origin = julian_day;
		ret = julian_day_2_julian_calendar(julian_day, &date); 
		if (WJTWL_SUCCESS != ret)
		{
			printf("something wrong in julian_day_2_julian_calendar with error numer %d, julian day %lld\n", ret, julian_day_origin);
			break;
		}
		else
		{
			ret = julian_calendar_2_julian_day(date, &julian_day);
			if (WJTWL_SUCCESS != ret)
			{
				printf("something wrong in julian_calendar_2_julian_day with error numer %d, julian day %lld\n", ret, julian_day_origin);
				break;
			}
			else
			{
				if (julian_day_origin != julian_day)
				{
					printf("test wrong julian day %lld\n", julian_day_origin);
					break;
				}
			}
		}
		if (0 == (julian_day % 10000000))
		{
			printf("test run julian day %lld\n", julian_day);
		}
	}
#endif // TEST_5


#if TEST_6
	jd_t julian_day, julian_day_origin;
	wjtwl_date_t date;
	for (julian_day = -166845060000; julian_day <= JULIAN_DAY_MAX; julian_day++)
	{
		julian_day_origin = julian_day;
		ret = julian_day_2_gregorian_calendar(julian_day, &date);
		if (WJTWL_SUCCESS != ret)
		{
			printf("something wrong in julian_day_2_julian_calendar with error numer %d, julian day %lld\n", ret, julian_day_origin);
			break;
		}
		else
		{
			ret = gregorian_calendar_2_julian_day(date, &julian_day);
			if (WJTWL_SUCCESS != ret)
			{
				printf("something wrong in julian_calendar_2_julian_day with error numer %d, julian day %lld\n", ret, julian_day_origin);
				break;
			}
			else
			{
				if (julian_day_origin != julian_day)
				{
					printf("test wrong julian day %lld\n", julian_day_origin);
					break;
				}
			}
		}
		if (0 == (julian_day % 10000000))
		{
			printf("test run julian day %lld\n", julian_day);
		}
	}
#endif // TEST_6

	getchar();

    return 0;
}


