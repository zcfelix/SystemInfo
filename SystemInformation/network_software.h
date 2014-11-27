#ifndef __NETWORK_SOFTWARE_H
#define __NETWORK_SOFTWARE_H

#include "software_info.h"
typedef enum __SoftwareType
{
	NETWORK_DISK,
	MAIL_CLIENT,
	ALL_SOFTWARE
}SoftwareType;

int  GetSpecificSoftwareList(std::vector<SoftwareInfo> *p_ss_list, SoftwareType st);
bool IsSpecificSoftware(SoftwareInfo *p_s_info, SoftwareType st);
int GetKeywords(SoftwareType ss, std::vector<std::wstring> *keywords);
#endif