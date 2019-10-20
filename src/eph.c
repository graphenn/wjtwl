#include "wjtwl_lib.h"
#include "eph.h"
#include "vsop.h"
#include "nutation.h"
#include "elp.h"
#include "wjtwl_math.h"
/*
�ڳ���������βʱ���Ժ�Ϊ��֤�����ԣ���Ҫ���ɵ����ڹ��㹫ʽ�����
��ʽֵΪ�������� * 2��
����ȡ600������ڡ�
*/
#define CALCULATE_DELTAT_JD_X2_INTERVAL (438291)


/*
* These coefficients represent the spline approximation discussed in the
* paper "Measurement of the Earth's Rotation: 720 BC to AD 2015",
* Stephenson, F.R., Morrison, L.V., and Hohenkerk, C.Y., published by
* Royal Society Proceedings A and available from their website at
* http://rspa.royalsocietypublishing.org/lookup/doi/10.1098/rspa.2016.0404
* Year numbers have been replaced by Julian day numbers by D. Koch.
* Year numbers �滻Ϊ Julian day numbers * 2������int�ͱ�ʾ���Ҿ����㹻��
* ϵ���滻Ϊԭϵ�� * 1024
* �����м��㹫ʽ��Ӧ���˵���
*/
#ifdef CHINESE_CALENDAR_HISTORY_SUPPORT
#define NDTCF16_HISTORY (27)
#else
#define NDTCF16_HISTORY (0)
#endif // CHINESE_CALENDAR_HISTORY_SUPPORT
#define NDTCF16 (NDTCF16_HISTORY +  30)

const int32_t dtcf16[NDTCF16][5] =
{
#ifdef CHINESE_CALENDAR_HISTORY_SUPPORT
	/*00*/{ 2916171,        0,         0,        0,        0 }, /* ybeg=     , yend= -720 */
	/*01*/{ 3734313, 21043807, -21778921, 12148140, -4650116 }, /* ybeg= -720, yend=  400 */
	/*02*/{ 4172605,  6762910,  -6124816,  -517215,  1382000 }, /* ybeg=  400, yend= 1000 */
	/*03*/{ 4537847,  1502878,  -2511039,  2519989, -1212169 }, /* ybeg= 1000, yend= 1500 */
	/*04*/{ 4610895,   299658,   -221514,   -44661,    58041 }, /* ybeg= 1500, yend= 1600 */
	/*05*/{ 4647421,    91525,    -68356,    32366,   -10749 }, /* ybeg= 1600, yend= 1650 */
	/*06*/{ 4698553,    44786,    -50220,      232,    16190 }, /* ybeg= 1650, yend= 1720 */
	/*07*/{ 4756993,    10988,     -1353,    63744,   -54217 }, /* ybeg= 1720, yend= 1800 */
	/*08*/{ 4764297,    19163,     -4564,    -1545,     2567 }, /* ybeg= 1800, yend= 1810 */
	/*09*/{ 4771601,    15621,        47,     6156,    -4745 }, /* ybeg= 1810, yend= 1820 */
	/*10*/{ 4778907,    17079,     -1875,    -8078,     3890 }, /* ybeg= 1820, yend= 1830 */
	/*11*/{ 4786211,    11016,     -6360,     3593,     -397 }, /* ybeg= 1830, yend= 1840 */
	/*12*/{ 4793517,     7852,      -366,     2401,     -346 }, /* ybeg= 1840, yend= 1850 */
	/*13*/{ 4797169,     9541,      1699,      340,     -954 }, /* ybeg= 1850, yend= 1855 */
	/*14*/{ 4800821,    10625,      -483,    -2522,     1634 }, /* ybeg= 1855, yend= 1860 */
	/*15*/{ 4804475,     9255,      -625,     2381,    -2557 }, /* ybeg= 1860, yend= 1865 */
	/*16*/{ 4808127,     8454,     -3533,    -5290,     2794 }, /* ybeg= 1865, yend= 1870 */
	/*17*/{ 4811779,     2426,     -5730,     3092,     -941 }, /* ybeg= 1870, yend= 1875 */
	/*18*/{ 4815431,    -1153,     -2367,      270,      -38 }, /* ybeg= 1875, yend= 1880 */
	/*19*/{ 4819085,    -3288,     -1939,      158,      575 }, /* ybeg= 1880, yend= 1885 */
	/*20*/{ 4822737,    -4493,       103,     1885,    -1473 }, /* ybeg= 1885, yend= 1890 */
	/*21*/{ 4826389,    -3977,      -544,    -2532,     1915 }, /* ybeg= 1890, yend= 1895 */
	/*22*/{ 4830041,    -5137,       137,     3213,     -238 }, /* ybeg= 1895, yend= 1900 */
	/*23*/{ 4833693,    -2024,      5852,     2502,    -1287 }, /* ybeg= 1900, yend= 1905 */
	/*24*/{ 4837345,     5041,      6992,    -1361,      737 }, /* ybeg= 1905, yend= 1910 */
	/*25*/{ 4840997,    11409,      6482,      851,     -845 }, /* ybeg= 1910, yend= 1915 */
	/*26*/{ 4844649,    17898,      5650,    -1682,      268 }, /* ybeg= 1915, yend= 1920 */
#endif // CHINESE_CALENDAR_HISTORY_SUPPORT
	/*27*/{ 4848303,    22136,      3092,     -877,        8 }, /* ybeg= 1920, yend= 1925 */
	/*28*/{ 4851955,    24360,      1365,     -851,      130 }, /* ybeg= 1925, yend= 1930 */
	/*29*/{ 4855607,    25004,        53,     -460,      145 }, /* ybeg= 1930, yend= 1935 */
	/*30*/{ 4859259,    24744,      -429,      -23,      719 }, /* ybeg= 1935, yend= 1940 */
	/*31*/{ 4862913,    25012,      1684,     2136,    -1133 }, /* ybeg= 1940, yend= 1945 */
	/*32*/{ 4866565,    27699,      2559,    -1262,      629 }, /* ybeg= 1945, yend= 1950 */
	/*33*/{ 4868757,    29626,      1154,      225,     -284 }, /* ybeg= 1950, yend= 1953 */
	/*34*/{ 4870947,    30722,       755,     -625,      646 }, /* ybeg= 1953, yend= 1956 */
	/*35*/{ 4873139,    31498,      1443,     1313,     -818 }, /* ybeg= 1956, yend= 1959 */
	/*36*/{ 4875331,    33436,      1615,    -1142,      519 }, /* ybeg= 1959, yend= 1962 */
	/*37*/{ 4877523,    34428,       889,      416,      204 }, /* ybeg= 1962, yend= 1965 */
	/*38*/{ 4879713,    35935,      2330,     1026,     -424 }, /* ybeg= 1965, yend= 1968 */
	/*39*/{ 4881905,    38867,      3108,     -248,      207 }, /* ybeg= 1968, yend= 1971 */
	/*40*/{ 4884097,    41934,      3233,      373,     -234 }, /* ybeg= 1971, yend= 1974 */
	/*41*/{ 4886289,    45306,      3275,     -331,      176 }, /* ybeg= 1974, yend= 1977 */
	/*42*/{ 4888479,    48426,      3143,      198,     -197 }, /* ybeg= 1977, yend= 1980 */
	/*43*/{ 4890671,    51570,      2947,     -393,       83 }, /* ybeg= 1980, yend= 1983 */
	/*44*/{ 4892863,    54206,      2410,     -143,     -170 }, /* ybeg= 1983, yend= 1986 */
	/*45*/{ 4895055,    56304,      1615,     -652,      459 }, /* ybeg= 1986, yend= 1989 */
	/*46*/{ 4897245,    57726,      1689,      726,     -284 }, /* ybeg= 1989, yend= 1992 */
	/*47*/{ 4899437,    59856,      2289,     -125,      114 }, /* ybeg= 1992, yend= 1995 */
	/*48*/{ 4901629,    62133,      2380,      217,     -323 }, /* ybeg= 1995, yend= 1998 */
	/*49*/{ 4903821,    64409,      1847,     -750,      115 }, /* ybeg= 1998, yend= 2001 */
	/*50*/{ 4906011,    65620,       691,     -406,      198 }, /* ybeg= 2001, yend= 2004 */
	/*51*/{ 4908203,    66104,       474,      188,       -8 }, /* ybeg= 2004, yend= 2007 */
	/*52*/{ 4910395,    66759,       828,      165,     -103 }, /* ybeg= 2007, yend= 2010 */
	/*53*/{ 4912587,    67649,       848,     -145,      172 }, /* ybeg= 2010, yend= 2013 */
	/*54*/{ 4914777,    68523,      1071,      369,     -289 }, /* ybeg= 2013, yend= 2016 */
	/*55*/{ 4916969,    69737,      1782,     -739,       88 }, /* ybeg= 2016, yend= 2019 ���ݵ�ǰ����������� */
	/*56*/{ 4923299,    70881,      5796,    -2496,     1287 }, /* ybeg= 2019, yend= 2027.10 ����Ԥ������������� */
};

/*
DeltaT = Ephemeris Time - Universal Time
���ȱ�����1/1024�룬Ҳ��1024=1�롣
���ڹ��㹫ʽ��������ʷ������ϡ�
*/
int32_t calculate_deltaT_extern(jd_t julian_day)
{
	int64_t t_temp;

	/*
	t = (Ygreg - 1825) / 100.0;
	dt = -320 + 32.5 * t * t;
	*/
	t_temp = julian_day / 5400 - 38202041;

	return (int32_t)(t_temp * t_temp / 10261699) - 327680;
}

/*
����DeltaT����ʽ
�������iΪ�������±꣬jdx2���������� * 2
*/
int32_t calculate_deltaT_polynomial(unsigned int i, int32_t jdx2)
{
	int64_t t_temp;

	/*
	���ȵ����¼��ɣ�����1120�ꡣͬʱ���Ǹ�����λ�����ᵼ�����һλ��׼����Ҫ������߾��ȣ�����16bit������������ѡ24bit��
	*/
	#define CALCULATE_DELTAT_T_SHIFT (24)

	t_temp = (((int64_t)jdx2 - dtcf16[i - 1][0]) << CALCULATE_DELTAT_T_SHIFT) / ((int64_t)dtcf16[i][0] - dtcf16[i - 1][0]);
	return (int32_t)(dtcf16[i][1] + (t_temp * (dtcf16[i][2] + ((t_temp * (dtcf16[i][3] + ((t_temp * dtcf16[i][4])
		>> CALCULATE_DELTAT_T_SHIFT))) >> CALCULATE_DELTAT_T_SHIFT)) >> CALCULATE_DELTAT_T_SHIFT));
}

/*
DeltaT = Ephemeris Time - Universal Time
�ο�
https://github.com/mivion/swisseph
https://eclipse.gsfc.nasa.gov/SEcat5/deltatpoly.html
���ȱ�����1/1024�룬Ҳ��1024=1�롣
�������ϣ�DeltaT�����Զ��������λ�ü�����
��Ŀǰ���ۼ����鹫ʽ����Ԫ4000��ʱDeltaTΪ4��Сʱ�࣬��Ԫǰ10000��ʱΪ5��ࡣ���ж�����ö�֪��
�˴�ʹ��stephenson_etc_2016���ȹ�ȥʹ�õ�stephenson_morrison_2004��׼ȷ��
��Ⱦɹ�ʽ���ڹ�Ԫ1600����1���Ӳ��졣
*/
int32_t calculate_deltaT(jd_t julian_day)
{
	unsigned int i;
	int32_t jdx2, delta_t;
	int64_t t_temp;

	/*
	��������������ת��Ϊ�������� * 2
	*/
	jdx2 = (int32_t)(julian_day / 43200);

	/*
	��ʼ���֮ǰ����ĩβ���֮��ʹ�ó��ڹ��㹫ʽ
	*/
	if ((jdx2 < dtcf16[0][0]) || (jdx2 >= dtcf16[NDTCF16 - 1][0]))
	{
		delta_t = calculate_deltaT_extern(julian_day);

		/*
		��֤�����ԣ��ڱ�ʼǰ������β֮�󣬹��ɵ����ڹ��㹫ʽ�����������ΪCALCULATE_DELTAT_JD_X2_INTERVAL��
		*/
#ifdef CHINESE_CALENDAR_HISTORY_SUPPORT
		if ((jdx2 >= dtcf16[0][0] - CALCULATE_DELTAT_JD_X2_INTERVAL) && (jdx2 < (dtcf16[0][0])))
		{
			delta_t = delta_t - (int32_t)(((int64_t)jdx2 - dtcf16[0][0] + CALCULATE_DELTAT_JD_X2_INTERVAL) * (calculate_deltaT_extern((jd_t)dtcf16[0][0] * 43200)
				- (int64_t)dtcf16[1][1]) / CALCULATE_DELTAT_JD_X2_INTERVAL);
		}
#endif // CHINESE_CALENDAR_HISTORY_SUPPORT

		if ((jdx2 >= dtcf16[NDTCF16 - 1][0]) && (jdx2 < (dtcf16[NDTCF16 - 1][0] + CALCULATE_DELTAT_JD_X2_INTERVAL)))
		{
			delta_t = delta_t + (int32_t)(((int64_t)jdx2 - dtcf16[NDTCF16 - 1][0] - CALCULATE_DELTAT_JD_X2_INTERVAL) * (calculate_deltaT_extern((jd_t)dtcf16[NDTCF16 - 1][0] * 43200)
				- (int64_t)calculate_deltaT_polynomial(NDTCF16 - 1, dtcf16[NDTCF16 - 1][0])) / CALCULATE_DELTAT_JD_X2_INTERVAL);
		}


	}
	else
	{
		for (i = 1; i < NDTCF16; i++) 
		{
			if (jdx2 < dtcf16[i][0]) 
			{
				break;
			}
		}

		delta_t = calculate_deltaT_polynomial(i, jdx2);
	}

	/*
	* All values of ��T based on Morrison and Stephenson [2016] assume a value for the Moon's secular acceleration of -25.82 arcsec/cy^2. 
	* ELP-2000 lunar ephemeris uses a slightly different value of -25.858 arcsec/cy^2
	* add a correction c = -0.000091 (-25.858 - (-25.82))(year-1955)^2  seconds
	* ���Ǻ�ȷ��1955����Ƿ���ҪУ����
	* ʵ���ϣ���1700�꣬Ҳ����0.2���ࡣ��Զ�Ĺ�ȥ��δ����DeltT��������Զ�ȴ�У������
	*/
	if (jdx2 < 4870217)
	{
		t_temp = julian_day / 1080 - 194808727;
		delta_t = delta_t + (int32_t)(t_temp * t_temp / 241111342912);
	}
		
	return delta_t;
}

/*����̫���ĵ��Ļƾ���longitude, latitude ������ǰ��̫�����Ļƾ��͵��Ļ�γ(��)��dt������ǧ����������ֵ��λ��*/
double AdjustSunEclipticLongitudeEC(double dt, double longitude, double latitude)
{
	double T = dt * 10; //T������������

	double dbLdash = longitude - 1.397 * T - 0.00031 * T * T;

	// ת��Ϊ����
	dbLdash *= RADIAN_PER_ANGLE;

	return (-0.09033 + 0.03916 * (cos(dbLdash) + sin(dbLdash)) * tan(latitude * RADIAN_PER_ANGLE)) / 3600.0;
}


/*�õ�ĳ�������յ�̫�����Ļƾ�(�ӻƾ�)����λ��*/
double GetSunEclipticLongitudeEC(double jde)
{
	double dt = (jde - JD2000) / 365250.0; /*����ǧ����*/

	// ����̫���ĵ��Ļƾ�
	double longitude = CalcSunEclipticLongitudeEC(dt);

	// ����̫���ĵ��Ļ�γ
	double latitude = CalcSunEclipticLatitudeEC(dt) * 3600.0;

	// ��������
	longitude += AdjustSunEclipticLongitudeEC(dt, longitude, latitude);

	// ���������¶�
	longitude += CalcEarthLongitudeNutation(dt);

	// �������в�
	/*̫�����Ļƾ����в���������: -20".4898/R*/
	longitude -= (20.4898 / CalcSunEarthRadius(dt)) / 3600.0;

	return longitude;
}

double GetMoonEclipticLongitudeEC(double dbJD)
{
	double Lp, D, M, Mp, F, E;
	double dt = (dbJD - JD2000) / 36525.0; /*����������*/

	GetMoonEclipticParameter(dt, &Lp, &D, &M, &Mp, &F, &E);

	/*����������Ļƾ�������*/
	double EI = CalcMoonECLongitudePeriodic(D, M, Mp, F, E);

	/*��������,ľ���Լ���������㶯*/
	EI += CalcMoonLongitudePerturbation(dt, Lp, F);

	/*����������Ļƾ�*/
	double longitude = Lp + EI / 1000000.0;

	/*���������¶�����*/
	longitude += CalcEarthLongitudeNutation(dt / 10.0);

	longitude = Mod360Degree(longitude); /*ӳ�䵽0-360��Χ��*/
	return longitude;
}

// ����ָ����ݵ����������angle�ǽ����ڻƵ��ϵĶ���
// ����ָ��������������ʱ��(��ѧʱ)
// �����޸ģ��������ռ���
double CalculateSolarTermsJD(double JD1, int angle)
{
	double JD0, stDegree, stDegreep;

	do
	{
		JD0 = JD1;
		stDegree = GetSunEclipticLongitudeEC(JD0);
		/*
			�Իƾ�0�ȵ����ƽ�ʱ�����ڽǶ�360��Բ���ԣ�����ƾ�ֵ������(345,360]��[0,15)�������䣬
			���ֵ����ǰһ�����䣬��Ҫ��������
		*/
		stDegree = ((angle == 0) && (stDegree > 345.0)) ? stDegree - 360.0 : stDegree;
		stDegreep = (GetSunEclipticLongitudeEC(JD0 + 0.000005)
			- GetSunEclipticLongitudeEC(JD0 - 0.000005)) / 0.00001;
		JD1 = JD0 - (stDegree - angle) / stDegreep;
	} while ((fabs(JD1 - JD0) > 0.0000001));

	return JD1;
}

/*
�õ�������ʱ������һ�����º�˷��ʱ�䣬ƽ�����С��3��
���������ָ��ʱ�����ѧʱ��������
����ֵ�����º�˷����ѧʱ��������
*/
double CalculateMoonShuoJD(double tdJD)
{
	double JD0, JD1, stDegree, stDegreep;

	JD1 = tdJD;
	do
	{
		JD0 = JD1;
		double moonLongitude = GetMoonEclipticLongitudeEC(JD0);
		double sunLongitude = GetSunEclipticLongitudeEC(JD0);
		if ((moonLongitude > 330.0) && (sunLongitude < 30.0))
		{
			sunLongitude = 360.0 + sunLongitude;
		}
		if ((sunLongitude > 330.0) && (moonLongitude < 30.0))
		{
			moonLongitude = 60.0 + moonLongitude;
		}

		stDegree = moonLongitude - sunLongitude;
		if (stDegree >= 360.0)
			stDegree -= 360.0;

		if (stDegree < -360.0)
			stDegree += 360.0;

		stDegreep = (GetMoonEclipticLongitudeEC(JD0 + 0.000005) - GetSunEclipticLongitudeEC(JD0 + 0.000005) - GetMoonEclipticLongitudeEC(JD0 - 0.000005) + GetSunEclipticLongitudeEC(JD0 - 0.000005)) / 0.00001;
		JD1 = JD0 - stDegree / stDegreep;
	} while ((fabs(JD1 - JD0) > 0.00000001));

	return JD1;
}