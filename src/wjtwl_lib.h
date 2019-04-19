#ifndef _wjtwl_lib_h_
#define _wjtwl_lib_h_

#include "wjtwl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define check_jd(jd)                                   \
{                                                      \
    if((jd < JULIAN_DAY_MIN) || (jd > JULIAN_DAY_MAX)) \
    {                                                  \
        return  WJTWL_ERROR_DATE;                      \
    }                                                  \
}

extern int g_time_zone;


#ifdef __cplusplus
}
#endif

#endif
