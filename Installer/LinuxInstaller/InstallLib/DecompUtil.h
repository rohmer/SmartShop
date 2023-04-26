#pragma once

#include <filesystem>
#include <sstream>
#include <string>

#include <archive.h>
#include <archive_entry.h>

#include "../../../Logger/Logger.h"

class DecompUtil
{
public:
	static bool DecompressZip(std::string zipFile, std::string destFolder);
	
private:
	static int copy_data(Logger *log, struct archive *ar, struct archive *aw);
};