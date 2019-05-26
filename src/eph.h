#ifndef _eph_h_
#define _eph_h_



#ifdef __cplusplus
extern "C" {
#endif

/*
DeltaT = Ephemeris Time - Universal Time
���ȱ�����1/1024�룬Ҳ��1024=1�롣
*/
int32_t calculate_deltaT(jd_t julian_day);

#ifdef __cplusplus
}
#endif

#endif
