#pragma once


struct FileSystemStats
{
public:	
	std::string filesystem;
	long files, free, freeFiles, total, usedPct, used, avail;
};