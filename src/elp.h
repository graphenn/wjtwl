#ifndef _elp_h_
#define _elp_h_



#ifdef __cplusplus
extern "C" {
#endif

void GetMoonEclipticParameter(double dt, double* Lp, double* D, double* M, double* Mp, double* F, double* E);

/*计算月球地心黄经周期项的和*/
double CalcMoonECLongitudePeriodic(double D, double M, double Mp, double F, double E);

/*计算金星摄动,木星摄动以及地球扁率摄动对月球地心黄经的影响,dt 是儒略世纪数，Lp和F单位是度*/
double CalcMoonLongitudePerturbation(double dt, double Lp, double F);

#ifdef __cplusplus
}
#endif

#endif
