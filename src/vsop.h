#ifndef _vsop_h_
#define _vsop_h_



#ifdef __cplusplus
extern "C" {
#endif

double CalcSunEclipticLongitudeEC(double dt);

double CalcSunEclipticLatitudeEC(double dt);

double CalcSunEarthRadius(double dt);

#ifdef __cplusplus
}
#endif

#endif
