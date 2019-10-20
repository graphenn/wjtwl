#include "wjtwl_lib.h"
#include "wjtwl_math.h"

double Mod360Degree(double degrees)
{
	double dbValue = degrees;

	while (dbValue < 0.0)
		dbValue += 360.0;

	while (dbValue > 360.0)
		dbValue -= 360.0;

	return dbValue;
}

double DegreeToRadian(double degree)
{
	return degree * PI / 180.0;
}