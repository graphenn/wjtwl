#include "wjtwl_lib.h"

/*
ʱ��Ĭ��ֵΪ+8��
����Ϊ��λ��Ҳ��+1��Ϊ3600��-1.5��Ϊ-5400
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
����
ʱ��������������Ҫ����ͳһ��ʱ������ͬʱ���������ϲ�ʵ�֡�ע�������ղ�����ʱ����ֱ��ʹ������ʱ��
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