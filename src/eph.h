#ifndef _eph_h_
#define _eph_h_



#ifdef __cplusplus
extern "C" {
#endif

/*
DeltaT = Ephemeris Time - Universal Time
精度保留到1/1024秒，也即1024=1秒。
*/
int32_t calculate_deltaT(jd_t julian_day);

// 计算指定年份的任意节气，angle是节气在黄道上的读数
// 返回指定节气的儒略日时间(力学时)
// 做了修改，按儒略日计算
double CalculateSolarTermsJD(double JD1, int angle);
/*
得到给定的时间后面第一个日月合朔的时间，平均误差小于3秒
输入参数是指定时间的力学时儒略日数
返回值是日月合朔的力学时儒略日数
*/
double CalculateMoonShuoJD(double tdJD);

/* for test */
/*得到某个儒略日的太阳地心黄经(视黄经)，单位度*/
double GetSunEclipticLongitudeEC(double jde);
/*得到某个儒略日的月亮地心黄经(视黄经)，单位度*/
double GetMoonEclipticLongitudeEC(double dbJD);

#ifdef __cplusplus
}
#endif

#endif
