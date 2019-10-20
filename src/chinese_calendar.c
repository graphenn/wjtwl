#include "wjtwl_lib.h"
#include "eph.h"
#include "wjtwl_math.h"

typedef int SOLAR_TERMS;

const int SOLAR_TERMS_COUNT = 24;

// 节气定义
const int VERNAL_EQUINOX = 0;    // 春分
const int CLEAR_AND_BRIGHT = 1;    // 清明
const int GRAIN_RAIN = 2;    // 谷雨
const int SUMMER_BEGINS = 3;    // 立夏
const int GRAIN_BUDS = 4;    // 小满
const int GRAIN_IN_EAR = 5;    // 芒种
const int SUMMER_SOLSTICE = 6;    // 夏至
const int SLIGHT_HEAT = 7;    // 小暑
const int GREAT_HEAT = 8;    // 大暑
const int AUTUMN_BEGINS = 9;    // 立秋
const int STOPPING_THE_HEAT = 10;   // 处暑
const int WHITE_DEWS = 11;   // 白露
const int AUTUMN_EQUINOX = 12;   // 秋分
const int COLD_DEWS = 13;   // 寒露
const int HOAR_FROST_FALLS = 14;   // 霜降
const int WINTER_BEGINS = 15;   // 立冬
const int LIGHT_SNOW = 16;   // 小雪
const int HEAVY_SNOW = 17;   // 大雪
const int WINTER_SOLSTICE = 18;   // 冬至
const int SLIGHT_COLD = 19;   // 小寒
const int GREAT_COLD = 20;   // 大寒
const int SPRING_BEGINS = 21;   // 立春
const int THE_RAINS = 22;   // 雨水
const int INSECTS_AWAKEN = 23;   // 惊蛰

double TdUtcDeltatT2(double jd2k)
{
	double julian_day_day;
	jd_t julian_day;
	int ret;

	julian_day_day = jd2k + JD2000;
	ret = julian_day_day_2_julian_day(julian_day_day, &julian_day);
	//TODO: 异常处理

	return (double)calculate_deltaT(julian_day) / 1024;
}

double JDUTCToLocalTime(double utcJD)
{
	return utcJD - (double)g_wjtwl_lib_config.time_zone / 86400;
}

double JDTDtoUTC(double tdJD)
{
	double jd2K = tdJD - JD2000;
	double tian = TdUtcDeltatT2(jd2K);
	tdJD -= tian;

	return tdJD;
}

double JDTDtoLocalTime(double tdJD)
{
	double tmp = JDTDtoUTC(tdJD);

	return JDUTCToLocalTime(tmp);
}

double GetInitialEstimateSolarTerms(int year, int angle)
{
	wjtwl_date_t date;
	jd_t julian_day;
	double julian_day_day;
	int ret;

	date.month = (int8_t)(ceil((angle + 90.0) / 30.0));
	date.month = date.month > 12 ? date.month - 12 : date.month;

	date.year = (int16_t)(year);
	date.hour = 12;
	date.minute = 0;
	date.second = 0;


	/* 每月第一个节气发生日期基本都4-9日之间，第二个节气的发生日期都在16－24日之间*/
	if ((angle % 15 == 0) && (angle % 30 != 0))
	{
		date.day = 6;
	}
	else
	{
		date.day = 20;
	}

	ret = calendar_2_julian_day(date, &julian_day);
	//TODO: 添加错误处理

	ret = julian_day_2_julian_day_day(julian_day, &julian_day_day);
	//TODO: 添加错误处理

	return julian_day_day;
}

// 计算指定年份的任意节气，angle是节气在黄道上的读数
// 返回指定节气的儒略日时间(力学时)
double CalculateSolarTerms(int year, int angle)
{
	double JD1;

	JD1 = GetInitialEstimateSolarTerms(year, angle);

	return CalculateSolarTermsJD(JD1, angle);
}

/*从某一年的某个节气开始，连续计算25个节气，返回各节气的儒略日，本地时间*/
void GetAllSolarTermsJD(int year, double* SolarTerms, int start)
{
	int i = 0;
	int st = start;
	while (i < 25)
	{
		double jd = CalculateSolarTerms(year, st * 15);
		SolarTerms[i++] = JDTDtoLocalTime(jd);
		if (st == WINTER_SOLSTICE)
		{
			year++;
		}
		st = (st + 1) % SOLAR_TERMS_COUNT;
	}
}