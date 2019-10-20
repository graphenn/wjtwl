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

// ����ָ����ݵ����������angle�ǽ����ڻƵ��ϵĶ���
// ����ָ��������������ʱ��(��ѧʱ)
// �����޸ģ��������ռ���
double CalculateSolarTermsJD(double JD1, int angle);
/*
�õ�������ʱ������һ�����º�˷��ʱ�䣬ƽ�����С��3��
���������ָ��ʱ�����ѧʱ��������
����ֵ�����º�˷����ѧʱ��������
*/
double CalculateMoonShuoJD(double tdJD);

/* for test */
/*�õ�ĳ�������յ�̫�����Ļƾ�(�ӻƾ�)����λ��*/
double GetSunEclipticLongitudeEC(double jde);
/*�õ�ĳ�������յ��������Ļƾ�(�ӻƾ�)����λ��*/
double GetMoonEclipticLongitudeEC(double dbJD);

#ifdef __cplusplus
}
#endif

#endif
