#ifndef __NETWORK_SOFTWARE_H
#define __NETWORK_SOFTWARE_H

#include "software_info.h"
int CreateNetworkDiskList(std::vector<SoftwareInfo> *p_nd_list);
bool IsNetworkDisk(SoftwareInfo *p_s_info);

#endif