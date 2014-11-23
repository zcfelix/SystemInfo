#ifndef __MAIL_CLIENT_H
#define __MAIL_CLIENT_H

#include "software_info.h"
int CreateMailClientList(std::vector<SoftwareInfo> *p_mc_list);
bool IsMailClient(SoftwareInfo *p_s_info);
#endif