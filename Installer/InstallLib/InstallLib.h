#pragma once 

#include <string>
#include <filesystem>
#include <string>
#include <sstream>
#include <stdio.h>
#include <archive_entry.h>
#include <ostream>
#include <iostream>
#include <archive.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "File.h"
#include "Version.h"
#include "PackageDescriptor.h"

class InstallLib
{
public:
	static bool CreateInstallPkg(std::string PackageDesc, PackageDescriptor packageDesc, std::string packageOutput);
	
	static bool InstallPackage(std::string PackageFile);

private:
	static bool unzipPackage(std::string PackageFile, std::string tmpDir);
	static int copy_data(struct archive *ar, struct archive *aw);
};