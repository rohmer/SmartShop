#pragma once

#include <string>
#include <vector>

#include <cJSON.h>
#include "FileDescriptor.h"
#include "Version.h"

struct PackageDescriptor
{
public:
	std::string PackageName, PackageDescription;
	Version PackageVersion;
	std::vector<FileDescriptor> PackageFiles;
	
	PackageDescriptor(
		std::string packageName,
		std::string packageDesc,
		Version packageVersion,
		std::vector<FileDescriptor> packageFile)
		: PackageName(packageName)
		, PackageDescription(packageDesc)
		, PackageVersion(packageVersion)
		, PackageFiles(packageFile)
	{
	}
	
	PackageDescriptor()
	{
	}
	
	static PackageDescriptor FromJSON(cJSON *json);
	cJSON *ToJSON();
};