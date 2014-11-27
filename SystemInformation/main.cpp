// SystemInformation.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "os_info.h"
#include "software_info.h"
#include "network_software.h"
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <locale>

static int SaveSoftwareInfo(std::vector<SoftwareInfo> *p_s_info, SoftwareType st = ALL_SOFTWARE);
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "");
	_setmode(_fileno(stdout), _O_U16TEXT);

	std::vector<SoftwareInfo> installed_software_list, network_disk_list, mail_client_list;
	GetInstalledSoftwareInfo(&installed_software_list);
	GetSpecificSoftwareList(&network_disk_list, NETWORK_DISK);
	GetSpecificSoftwareList(&mail_client_list, MAIL_CLIENT);

	SaveSoftwareInfo(&installed_software_list);
	SaveSoftwareInfo(&network_disk_list, NETWORK_DISK);
	SaveSoftwareInfo(&mail_client_list, MAIL_CLIENT);
	return 0;
}

static int SaveSoftwareInfo(std::vector<SoftwareInfo> *p_s_info, SoftwareType st)
{
	int ret_val = 0;
	std::string file_name;
	switch (st)
	{
	case ALL_SOFTWARE:
		file_name = "_installed_software_list.txt";
		break;
	case MAIL_CLIENT:
		file_name = "_mail_client_list.txt";
		break;
	case NETWORK_DISK:
		file_name = "_network_disk_list.txt";
		break;
	}
	const TCHAR *format = _T("name: %s\nversion: %s\npublisher: %s\nsize: %s\ninstall date: %s\ninstall location: %\s\n\n\n");
	FILE *out_file;
	if (NULL == fopen_s(&out_file, file_name.c_str(), "w, ccs=UNICODE"))
	{
		for (auto iter = p_s_info->begin(); iter != p_s_info->end(); ++iter)
		{
			if (!(iter->name).empty())
			{
				fwprintf(out_file, format, iter->name.c_str(), iter->version.c_str(), iter->publisher.c_str(),
					iter->size.c_str(), iter->install_date.c_str(), iter->install_location.c_str());
			}
		}
		fclose(out_file);
		ret_val = 0;
	}
	else
	{
		std::wcerr << _T("Open file failed") << std::endl;
		ret_val = -1;
	}
	return ret_val;
}