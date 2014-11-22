#include "stdafx.h"
#include "software_info.h"
#include <iostream>
#include <sstream>
#include <iomanip>

LPCTSTR const software_key_path = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
int GetInstalledSoftwareInfo(std::vector<SoftwareInfo> *p_s_info_list)
{
	HKEY h_key;
	long access_flag = KEY_ALL_ACCESS;
	int access_times = 0;
	while (access_times < 2)
	{
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, software_key_path, 0, access_flag, &h_key) != ERROR_SUCCESS)
		{
			std::wcerr << _T("´ò¿ª×¢²á±íÊ§°Ü!") << std::endl;
			return -1;
		}
		InsideSoftwareKeyForInfo(p_s_info_list, &h_key, access_flag);
		++access_times;
		access_flag = KEY_ALL_ACCESS | KEY_WOW64_64KEY;
	}
	return 0;
}

int InsideSoftwareKeyForInfo(std::vector<SoftwareInfo> *p_s_info_list, HKEY *h_key, long access_flag)
{
	DWORD index = 0;
	TCHAR sub_key_name[MAX_PATH] = { 0 };
	DWORD key_length = MAX_PATH * sizeof(TCHAR);
	LONG  ret;
	HKEY  h_item;
	SoftwareInfo software_info;
	while ((ret = RegEnumKeyEx(*h_key, index, sub_key_name, &key_length, NULL, NULL, NULL, NULL)) != ERROR_NO_MORE_ITEMS)
	{
		if (ret == ERROR_SUCCESS)
		{
			TCHAR sub_key_path[MAX_PATH];
			DWORD software_size = 0;
			DWORD size_len = sizeof(DWORD);
			wsprintf(sub_key_path, _T("%s\\%s"), software_key_path, sub_key_name);
			if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, sub_key_path, 0, access_flag, &h_item) == ERROR_SUCCESS)
			{
				QuerySoftwareInfoValue(&software_info, &h_item);
				(*p_s_info_list).push_back(software_info);
				memset(&software_info, 0, sizeof(SoftwareInfo));
			}
		}
		key_length = MAX_PATH * sizeof(TCHAR);
		++index;
	}
	return 0;
}

int QuerySoftwareInfoValue(SoftwareInfo *p_s_info, HKEY *h_item)
{
	DWORD reg_type = REG_BINARY | REG_DWORD | REG_EXPAND_SZ | REG_MULTI_SZ | REG_NONE | REG_SZ;
	TCHAR buffer[MAX_PATH] = { 0 };
	DWORD buffer_len = sizeof(TCHAR)* MAX_PATH;
	DWORD estimated_size = 0;
	DWORD size_len = sizeof(DWORD);

	RegQueryValueEx(*h_item, _T("DisplayName"), NULL, &reg_type, (LPBYTE)buffer, &buffer_len);
	p_s_info->name = buffer;

	buffer_len = sizeof(TCHAR)* MAX_PATH;
	memset(buffer, 0, buffer_len);
	RegQueryValueEx(*h_item, _T("DisPlayVersion"), NULL, &reg_type, (LPBYTE)buffer, &buffer_len);
	p_s_info->version = buffer;

	buffer_len = sizeof(TCHAR)* MAX_PATH;
	memset(buffer, 0, buffer_len);
	RegQueryValueEx(*h_item, _T("Publisher"), NULL, &reg_type, (LPBYTE)buffer, &buffer_len);
	p_s_info->publisher = buffer;

	buffer_len = sizeof(TCHAR)* MAX_PATH;
	memset(buffer, 0, buffer_len);
	RegQueryValueEx(*h_item, _T("InstallDate"), NULL, &reg_type, (LPBYTE)buffer, &buffer_len);
	p_s_info->install_date = buffer;

	buffer_len = sizeof(TCHAR)* MAX_PATH;
	memset(buffer, 0, buffer_len);
	RegQueryValueEx(*h_item, _T("InstallLocation"), NULL, &reg_type, (LPBYTE)buffer, &buffer_len);
	p_s_info->install_location = buffer;

	RegQueryValueEx(*h_item, _T("EstimatedSize"), NULL, &reg_type, (LPBYTE)&estimated_size, &size_len);
	if (estimated_size == 0)
	{
		p_s_info->size = _T("");
	}
	else
	{
		std::wstringstream ss;
		ss << std::fixed << std::setprecision(1) << estimated_size / 1024.0 << "MB";
		p_s_info->size = ss.str();
	}
	return 0;
}