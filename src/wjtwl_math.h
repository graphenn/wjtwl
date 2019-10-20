#ifndef _wjtwl_math_h_
#define _wjtwl_math_h_

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PI 3.1415926535897932384626433832795
#define RADIAN_PER_ANGLE (PI / 180.0)
#define JD2000 2451545.0

#define COUNT_OF(element)  (sizeof(element) / sizeof(element[0]))

double Mod360Degree(double degrees);
double DegreeToRadian(double degree);

#ifdef __cplusplus
}
#endif

#endif
