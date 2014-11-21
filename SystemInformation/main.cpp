// SystemInformation.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "os_info.h"
#include "software_info.h"
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <sstream>

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "");
	_setmode(_fileno(stdout), _O_U16TEXT);

	//OsInfo *p_my_os_info = new OsInfo;
	//GetOsInfo(p_my_os_info);
	//
	//std::wcout << p_my_os_info->os_version << std::endl << p_my_os_info->pc_name << std::endl << p_my_os_info->system_dir
	//	<< std::endl << p_my_os_info->windows_dir << std::endl << p_my_os_info->mem_size << std::endl;
	//
	//for (auto iter = p_my_os_info->drive_info_list.begin(); iter != p_my_os_info->drive_info_list.end(); ++iter)
	//{
	//	std::wcout << iter->letter << " " << iter->name << " " << iter->type << " " << iter->file_system << std::endl;
	//	std::wcout << iter->total_bytes.QuadPart / 1024.0 / 1024.0 / 1024.0 << " " << iter->free_bytes.QuadPart / 1024.0 / 1024.0 / 1024.0 << " " << iter->free_available_bytes.QuadPart / 1024.0 / 1024.0 / 1024.0 << std::endl;
	//}
	//delete p_my_os_info;

	std::vector<SoftwareInfo> software_info_list;
	GetInstalledSoftwareInfo(&software_info_list);

	FILE *out_file;
	fopen_s(&out_file, "installed_software.txt", "w, ccs=UNICODE");
	for (auto iter = software_info_list.begin(); iter != software_info_list.end(); ++iter)
	{
		if (iter->name[0] != '\0')
		{
			fwprintf(out_file, _T("%s\n"), iter->name.c_str());
		}
	}
	return 0;
}

