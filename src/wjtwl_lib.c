#include "wjtwl_lib.h"

/*
时区默认值为+8区
以秒为单位，也即+1区为3600，-1.5区为-5400
*/
SPEC___THREAD wjtwl_lib_config_t g_wjtwl_lib_config = {
.time_zone = 28800
};

int wjtwl_get_features(wjtwl_features_t *wjtwl_features)
{
	wjtwl_features->version_major = WJTWL_VERSION_MAJOR;
	wjtwl_features->version_minor = WJTWL_VERSION_MINOR;
#ifdef CHINESE_CALENDAR_HISTORY_SUPPORT
	wjtwl_features->chinese_calendar_history_support = true;
#else
	wjtwl_features->chinese_calendar_history_support = false;
#endif

	return WJTWL_SUCCESS;
}

/*
设置
时区：本天文历需要设置统一的时区，不同时区计算在上层实现。注意儒略日不区分时区，直接使用世界时。
*/
int wjtwl_set_config(const wjtwl_config_t *wjtwl_config)
{
	if ((wjtwl_config->time_zone < -12.0f) || (wjtwl_config->time_zone > 14.0f))
	{
		return WJTWL_ERROR_DATE;
	}

	g_wjtwl_lib_config.time_zone = (int)(wjtwl_config->time_zone * 3600);

	return WJTWL_SUCCESS;
}

int wjtwl_get_config(wjtwl_config_t *wjtwl_config)
{
	wjtwl_config->time_zone = (float)g_wjtwl_lib_config.time_zone / 3600;
	return WJTWL_SUCCESS;
}