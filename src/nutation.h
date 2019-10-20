#ifndef _nutation_h_
#define _nutation_h_



#ifdef __cplusplus
extern "C" {
#endif

//天体章动系数类型变量
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

/*计算某时刻的黄经章动干扰量，dt是儒略千年数，返回值单位是度*/
double CalcEarthLongitudeNutation(double dt);


#ifdef __cplusplus
}
#endif

#endif
