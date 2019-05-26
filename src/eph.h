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

#ifdef __cplusplus
}
#endif

#endif
