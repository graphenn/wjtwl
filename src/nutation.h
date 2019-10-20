#ifndef _nutation_h_
#define _nutation_h_



#ifdef __cplusplus
extern "C" {
#endif

//�����¶�ϵ�����ͱ���
typedef struct
{
	double   D;
	double   M;
	double   Mp;
	double   F;
	double   omega;
	double   sine1;
	double   sine2;
	double   cosine1;
	double   cosine2;
}NUTATION_COEFFICIENT;


extern const NUTATION_COEFFICIENT nutation[63];

void GetEarthNutationParameter(double dt, double* D, double* M, double* Mp, double* F, double* Omega);

/*����ĳʱ�̵Ļƾ��¶���������dt������ǧ����������ֵ��λ�Ƕ�*/
double CalcEarthLongitudeNutation(double dt);


#ifdef __cplusplus
}
#endif

#endif
