#include "stdafx.h"
#include "hardware_info.h"

int HardDiskNumber()
{
	int disk_count = 0;
	DWORD d = GetLogicalDrives();
	while (d)
	{
		if (d & 1)
			++disk_count;
		d = d >> 1;
	}

	return disk_count;
}

int HardDiskSize(PULARGE_INTEGER *total_bytes, PULARGE_INTEGER *free_bytes, 
	PULARGE_INTEGER *free_availabel_bytes)
{
	DWORD d = GetLogicalDrives();
	TCHAR drive_dir[] = L"A:\\";
	for (int i = 0; i < 26; ++i)
	{
		if (d & (1 << i))
		{
			drive_dir[0] = L'A' + i;
			GetDiskFreeSpaceEx(drive_dir, (PULARGE_INTEGER)free_availabel_bytes,
				(PULARGE_INTEGER)total_bytes, (PULARGE_INTEGER)free_bytes);

		}
	}
}