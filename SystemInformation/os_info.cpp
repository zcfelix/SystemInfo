#include "stdafx.h"
#include "os_info.h"
#include <VersionHelpers.h>
#include <iostream>

int GetOsInfo(OsInfo *p_os_info)
{
	std::wstring win_version;
	win_version = GetWindowsVersion();
	p_os_info->os_version = win_version;

	TCHAR buffer[MAX_PATH];
	DWORD len = sizeof(TCHAR)* MAX_PATH;
	GetComputerName(buffer, &len);
	p_os_info->pc_name = buffer;

	MEMORYSTATUS mem_status;
	GlobalMemoryStatus(&mem_status);
	p_os_info->mem_size = mem_status.dwTotalPhys;

	len = sizeof(TCHAR)* MAX_PATH;
	GetWindowsDirectory(buffer, len);
	p_os_info->windows_dir = buffer;

	GetSystemDirectory(buffer, len);
	p_os_info->system_dir = buffer;

	GetDriveInfo(p_os_info);

	return 0;
}

std::wstring GetWindowsVersion()
{
	std::wstring win_version;
	if (IsWindowsXPOrGreater())
		win_version = L"Windows XP";
	if (IsWindowsXPSP1OrGreater())
		win_version = L"Windows XP SP1";
	if (IsWindowsXPSP2OrGreater())
		win_version = L"Windows XP SP2";
	if (IsWindowsXPSP3OrGreater())
		win_version = L"Windows XP SP3";
	if (IsWindowsVistaOrGreater())
		win_version = L"Windows Vista";
	if (IsWindowsVistaSP1OrGreater())
		win_version = L"Windows Vista SP1";
	if (IsWindowsVistaSP2OrGreater())
		win_version = L"Windows Vista SP2";
	if (IsWindows7OrGreater())
		win_version = L"Windows 7";
	if (IsWindows7SP1OrGreater())
		win_version = L"Windows 7 SP1";
	if (IsWindows8OrGreater())
		win_version = L"Windows 8";
	if (IsWindows8Point1OrGreater)
		win_version = L"Windows 8.1";
	if (IsWindowsServer())
		win_version = L"Windows Server";

	return win_version;
}

int GetDriveInfo(OsInfo *p_os_info)
{
	DriveInfo drive_info;
	PULARGE_INTEGER total_bytes, free_bytes, free_available_bytes;

	DWORD drives = GetLogicalDrives();
	for (int i = 0; i < 26; i++)
	{
		if ( drives & (1 << i) )
		{
			drive_info.letter = L'A' + i;

			TCHAR drive_path[] = { L'A' + i, L':', L'\\', L'\0' };
			TCHAR drive_fs[10], drive_name[MAX_PATH];
			GetVolumeInformation(drive_path, drive_name, MAX_PATH + 1, NULL, NULL, NULL, drive_fs, MAX_PATH + 1);
			drive_info.name = drive_name;
			drive_info.file_system = drive_fs;

			UINT type = GetDriveType(drive_path);
			switch (type)
			{
			case DRIVE_UNKNOWN:
				drive_info.type = L"Unknown";
				break;
			case DRIVE_NO_ROOT_DIR:
				drive_info.type = L"No this root dir";
				break;
			case DRIVE_REMOVABLE:
				drive_info.type = L"Removable drive";
				break;
			case DRIVE_FIXED:
				drive_info.type = L"Fixed drive";
				break;
			case DRIVE_REMOTE:
				drive_info.type = L"Remote drive";
				break;
			case DRIVE_CDROM:
				drive_info.type = L"CD-ROM";
				break;
			case DRIVE_RAMDISK:
				drive_info.type = L"RAM";
				break;
			default:
				drive_info.type = L"Error";
			}
			p_os_info->drive_info_list.push_back(drive_info);
		}
	}
	return 0;
}