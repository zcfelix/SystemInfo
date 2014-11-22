#ifndef __SOFTWARE_INFO_H
#define __SOFTWARE_INFO_H

#include "stdafx.h"
#include <functional>
typedef struct __SoftwareInfo
{
	std::wstring name;
	std::wstring version;
	std::wstring install_date;
	std::wstring publisher;
	std::wstring install_location;
	std::wstring size;
}SoftwareInfo;

int GetInstalledSoftwareInfo(std::vector<SoftwareInfo> *p_s_info_list);
int InsideSoftwareKeyForInfo(std::vector<SoftwareInfo> *p_s_info_list, HKEY *h_key, long access_flag );
int QuerySoftwareInfoValue(SoftwareInfo *p_s_info, HKEY *h_item);
#endif