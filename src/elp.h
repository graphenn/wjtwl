#ifndef _elp_h_
#define _elp_h_



#ifdef __cplusplus
extern "C" {
#endif

void GetMoonEclipticParameter(double dt, double* Lp, double* D, double* M, double* Mp, double* F, double* E);

/*����������Ļƾ�������ĺ�*/
double CalcMoonECLongitudePeriodic(double D, double M, double Mp, double F, double E);

/*��������㶯,ľ���㶯�Լ���������㶯��������Ļƾ���Ӱ��,dt ��������������Lp��F��λ�Ƕ�*/
double CalcMoonLongitudePerturbation(double dt, double Lp, double F);

#ifdef __cplusplus
}
#endif

#endif
