#ifndef __HARDWARE_INFO_H
#define __HARDWARE_INFO_H

#include "stdafx.h"

typedef struct __HardDiskInfo
{
	TCHAR letter;
	PULARGE_INTEGER total_bytes;
	PULARGE_INTEGER free_bytes;
	PULARGE_INTEGER free_available_bytes;
}HardDiskInfo;

int HardDiskNumber();
int HardDiskSize(PULARGE_INTEGER *total_bytes, PULARGE_INTEGER *free_bytes, 
	PULARGE_INTEGER *free_availabel_bytes);

#endif