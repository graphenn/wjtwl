#include "wjtwl_lib.h"

/*
保存时区的变量，默认值为+8区
以秒为单位，也即+1区为3600，-1.5区为-5400
*/
int g_time_zone = 28800;

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

	g_time_zone = (int)(wjtwl_config->time_zone * 3600);

	return WJTWL_SUCCESS;
}

int wjtwl_get_config(wjtwl_config_t *wjtwl_config)
{
	wjtwl_config->time_zone = (float)g_time_zone / 3600;
	return WJTWL_SUCCESS;
}