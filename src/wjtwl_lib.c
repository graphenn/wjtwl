#include "wjtwl_lib.h"

/*
����ʱ���ı�����Ĭ��ֵΪ+8��
����Ϊ��λ��Ҳ��+1��Ϊ3600��-1.5��Ϊ-5400
*/
int g_time_zone = 28800;

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

	g_time_zone = (int)(wjtwl_config->time_zone * 3600);

	return WJTWL_SUCCESS;
}

int wjtwl_get_config(wjtwl_config_t *wjtwl_config)
{
	wjtwl_config->time_zone = (float)g_time_zone / 3600;
	return WJTWL_SUCCESS;
}