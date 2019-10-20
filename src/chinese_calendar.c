#include "wjtwl_lib.h"
#include "eph.h"
#include "wjtwl_math.h"

typedef int SOLAR_TERMS;

const int SOLAR_TERMS_COUNT = 24;

// ��������
const int VERNAL_EQUINOX = 0;    // ����
const int CLEAR_AND_BRIGHT = 1;    // ����
const int GRAIN_RAIN = 2;    // ����
const int SUMMER_BEGINS = 3;    // ����
const int GRAIN_BUDS = 4;    // С��
const int GRAIN_IN_EAR = 5;    // â��
const int SUMMER_SOLSTICE = 6;    // ����
const int SLIGHT_HEAT = 7;    // С��
const int GREAT_HEAT = 8;    // ����
const int AUTUMN_BEGINS = 9;    // ����
const int STOPPING_THE_HEAT = 10;   // ����
const int WHITE_DEWS = 11;   // ��¶
const int AUTUMN_EQUINOX = 12;   // ���
const int COLD_DEWS = 13;   // ��¶
const int HOAR_FROST_FALLS = 14;   // ˪��
const int WINTER_BEGINS = 15;   // ����
const int LIGHT_SNOW = 16;   // Сѩ
const int HEAVY_SNOW = 17;   // ��ѩ
const int WINTER_SOLSTICE = 18;   // ����
const int SLIGHT_COLD = 19;   // С��
const int GREAT_COLD = 20;   // ��
const int SPRING_BEGINS = 21;   // ����
const int THE_RAINS = 22;   // ��ˮ
const int INSECTS_AWAKEN = 23;   // ����

double TdUtcDeltatT2(double jd2k)
{
	double julian_day_day;
	jd_t julian_day;
	int ret;

	julian_day_day = jd2k + JD2000;
	ret = julian_day_day_2_julian_day(julian_day_day, &julian_day);
	//TODO: �쳣����

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


	/* ÿ�µ�һ�������������ڻ�����4-9��֮�䣬�ڶ��������ķ������ڶ���16��24��֮��*/
	if ((angle % 15 == 0) && (angle % 30 != 0))
	{
		date.day = 6;
	}
	else
	{
		date.day = 20;
	}

	ret = calendar_2_julian_day(date, &julian_day);
	//TODO: ��Ӵ�����

	ret = julian_day_2_julian_day_day(julian_day, &julian_day_day);
	//TODO: ��Ӵ�����

	return julian_day_day;
}

// ����ָ����ݵ����������angle�ǽ����ڻƵ��ϵĶ���
// ����ָ��������������ʱ��(��ѧʱ)
double CalculateSolarTerms(int year, int angle)
{
	double JD1;

	JD1 = GetInitialEstimateSolarTerms(year, angle);

	return CalculateSolarTermsJD(JD1, angle);
}

/*��ĳһ���ĳ��������ʼ����������25�����������ظ������������գ�����ʱ��*/
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