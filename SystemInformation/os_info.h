#ifndef __OS_INFO_H
#define __OS_INFO_H

#include "stdafx.h"

typedef struct __DriveInfo
{
	TCHAR letter;				
	std::wstring name;
	std::wstring type;
	std::wstring file_system;
}DriveInfo;

typedef struct __OsInfo
{
	std::wstring os_version;
	std::wstring pc_name;
	SIZE_T mem_size;
	std::wstring system_dir;
	std::wstring windows_dir;
	std::vector<DriveInfo> drive_info_list;
}OsInfo;

std::wstring GetWindowsVersion();
int GetOsInfo(OsInfo *p_os_info);
int GetDriveInfo(OsInfo *p_os_info);

#endif 