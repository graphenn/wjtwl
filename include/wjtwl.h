#ifndef _wjtwl_h_
#define _wjtwl_h_

#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/*������*/
#define WJTWL_SUCCESS    (0)
#define WJTWL_ERROR_DATE (1)

/*
time_zone��ʱ��
*/
typedef struct
{
	float time_zone;
} wjtwl_config_t;

/* B.C: 10000-1-1-00-00-00 UT+14*/
#define JULIAN_DAY_MIN (-166845060000)
/*A.D. 4000-12-31-23-59-59 UT-12*/
#define JULIAN_DAY_MAX (274959014399)
/*
Julian day�������գ�����Ϊ��λ��
�����ת��Ϊ����Ϊ��λ�����Գ���86400
*/
typedef int_least64_t jd_t;

/*
��С�ڵ���0ʱ����ʾ��Ԫǰ��1 - year���꣬����0��ʾ��Ԫǰ1�꣬-134��ʾ��Ԫǰ135�ꡣ
��������ʱ�����������롣
��Ϊ�������ʱ��hour/minute/second֧������Ϊ-1����ʱ�ֱ��ЧΪ0ʱ0��0�֡�
��Ϊ�������ʱ��weak����Ч��
*/
typedef struct
{
	int16_t year;
	int8_t month;
	int8_t day;
	int8_t hour;
	int8_t minute;
	int8_t second;
	int8_t weak;
} wjtwl_date_t;

/*
����
ʱ��������������Ҫ����ͳһ��ʱ������ͬʱ���������ϲ�ʵ�֡�ע�������ղ�����ʱ����ֱ��ʹ������ʱ��
*/
int wjtwl_set_config(const wjtwl_config_t *wjtwl_config);
int wjtwl_get_config(wjtwl_config_t *wjtwl_config);

/*����������Ϊ��λ������Ϊ��λ��ת��ͬʱ֧�ּ�������*/
int julian_day_2_julian_day_day(jd_t julian_day, double *julian_day_day);
int julian_day_day_2_julian_day(double julian_day_day, jd_t *julian_day);

/*�������������ջ�ת*/
int modified_julian_day_2_julian_day(jd_t modified_julian_day, jd_t *julian_day);
int julian_day_2_modified_julian_day(jd_t julian_day, jd_t *modified_julian_day);

/*���������ջ�ת*/
int calendar_2_julian_day(wjtwl_date_t calendar, jd_t *julian_day);
int julian_day_2_calendar(jd_t julian_day, wjtwl_date_t *calendar);

/*��������������ջ�ת*/
int gregorian_calendar_2_julian_day(wjtwl_date_t gregorian_calendar, jd_t *julian_day);
int julian_day_2_gregorian_calendar(jd_t julian_day, wjtwl_date_t *gregorian_calendar);

/*�����������ջ�ת*/
int julian_calendar_2_julian_day(wjtwl_date_t julian_calendar, jd_t *julian_day);
int julian_day_2_julian_calendar(jd_t julian_day, wjtwl_date_t *julian_calendar);


#ifdef __cplusplus
}
#endif

#endif
