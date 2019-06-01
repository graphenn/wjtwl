#ifndef _wjtwl_lib_h_
#define _wjtwl_lib_h_

#include "wjtwl.h"
#include "wjtwl_lib_config.h"

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

/*
time_zone£¬Ê±Çø
*/
typedef struct
{
	int time_zone;
} wjtwl_lib_config_t;

extern SPEC___THREAD wjtwl_lib_config_t g_wjtwl_lib_config;


#ifdef __cplusplus
}
#endif

#endif
