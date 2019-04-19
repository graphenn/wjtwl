#ifndef _wjtwl_h_
#define _wjtwl_h_

#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/*错误码*/
#define WJTWL_SUCCESS    (0)
#define WJTWL_ERROR_DATE (1)

/*
time_zone，时区
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
Julian day，儒略日，以秒为单位。
如果想转换为以日为单位，可以除以86400
*/
typedef int_least64_t jd_t;

/*
年小于等于0时，表示公元前（1 - year）年，例如0表示公元前1年，-134表示公元前135年。
采用世界时，不存在闰秒。
作为输入参数时，hour/minute/second支持设置为-1，此时分别等效为0时0点0分。
作为输入参数时，weak不生效。
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
设置
时区：本天文历需要设置统一的时区，不同时区计算在上层实现。注意儒略日不区分时区，直接使用世界时。
*/
int wjtwl_set_config(const wjtwl_config_t *wjtwl_config);
int wjtwl_get_config(wjtwl_config_t *wjtwl_config);

/*儒略日以秒为单位和以日为单位互转，同时支持简化儒略历*/
int julian_day_2_julian_day_day(jd_t julian_day, double *julian_day_day);
int julian_day_day_2_julian_day(double julian_day_day, jd_t *julian_day);

/*简化儒略日儒略日互转*/
int modified_julian_day_2_julian_day(jd_t modified_julian_day, jd_t *julian_day);
int julian_day_2_modified_julian_day(jd_t julian_day, jd_t *modified_julian_day);

/*公历儒略日互转*/
int calendar_2_julian_day(wjtwl_date_t calendar, jd_t *julian_day);
int julian_day_2_calendar(jd_t julian_day, wjtwl_date_t *calendar);

/*格里高利历儒略日互转*/
int gregorian_calendar_2_julian_day(wjtwl_date_t gregorian_calendar, jd_t *julian_day);
int julian_day_2_gregorian_calendar(jd_t julian_day, wjtwl_date_t *gregorian_calendar);

/*儒略历儒略日互转*/
int julian_calendar_2_julian_day(wjtwl_date_t julian_calendar, jd_t *julian_day);
int julian_day_2_julian_calendar(jd_t julian_day, wjtwl_date_t *julian_calendar);


#ifdef __cplusplus
}
#endif

#endif
