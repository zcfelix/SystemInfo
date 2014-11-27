#include "stdafx.h"
#include "network_software.h"
#include "software_info.h"

int  GetSpecificSoftwareList(std::vector<SoftwareInfo> *p_ss_list, SoftwareType st)
{
	std::vector<SoftwareInfo> installed_software_list;
	GetInstalledSoftwareInfo(&installed_software_list);

	for (auto iter = installed_software_list.begin(); iter != installed_software_list.end(); ++iter)
	{
		if (true == IsSpecificSoftware(&(*iter), st))
			(*p_ss_list).push_back(*iter);
	}
	return 0;
}

bool IsSpecificSoftware(SoftwareInfo *p_s_info, SoftwareType st)
{
	std::vector<std::wstring> keywords;
	bool ret = false;

	if (0 != GetKeywords(st, &keywords))
		return ret;

	std::wstring software_name(p_s_info->name);
	for (auto iter = keywords.begin(); iter != keywords.end(); ++iter)
	{
		if (software_name.find(*iter) != std::wstring::npos)
		{
			ret = true;
			break;
		}
	}
	return ret;
}

int GetKeywords(SoftwareType st, std::vector<std::wstring> *keywords)
{
	std::vector<std::wstring> network_disk_keywords{ _T("∞Ÿ∂»‘∆"), _T("Œ¢‘∆"), _T("Õ¯≈Ã"), _T("Dropbox"), 
		_T("yunfile"),_T("“◊≈Ã"), _T("howfile"), _T("raysource"), _T("Skydrive"), _T("‘∆≈Ã") };

	std::vector<std::wstring> mail_client_keywords{ _T("Outlook"), _T("Thunderbird"), _T("Foxmail"),
		_T("SeaMonkey"), _T("KMail"), _T("Sylpheed"), _T("DreamMail") };

	switch (st)
	{
	case NETWORK_DISK:
		*keywords = network_disk_keywords;
		break;
	case MAIL_CLIENT:
		*keywords = mail_client_keywords;
		break;
	default:
		return -1;
	}
	return 0;
}