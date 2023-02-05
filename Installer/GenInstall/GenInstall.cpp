#include <filesystem>
#include <fstream>
#include <iostream>

#include <cjson/cJSON.h>

#include "Options.h"
#include "File.h"
#include "PackageDescriptor.h"
#include "InstallLib.h"

using namespace std;
std::string Options::packageName;

int main(int argc, char *argv[])
{
	if (!std::filesystem::exists("package.json"))
	{
		std::cout << "No package.json available or writiable\n\nExiting\n\n";
		return -1;
	}
	
	std::fstream istream("package.json");
	std::stringstream pjson;
	std::string line;
	while (getline(istream, line))
	{
		pjson << line << "\n";
	}
		
	
	PackageDescriptor desc;
	try
	{
		cJSON *json = cJSON_Parse(pjson.str().c_str());
		desc = PackageDescriptor::FromJSON(json);
	}
	catch (const std::exception&e)
	{
		std::cout << "Failed to parse package.json, " << e.what() << "\n\n";
		return -1;
	}
	
	std::string packageName;
	if (Options::packageName.length() > 0)
		packageName = Options::packageName;
	else
		packageName = desc.SoftwareName;
	
	try
	{
		if (InstallLib::CreateInstallPkg("package.json", desc, packageName))
		{
			std::cout << "Created package: " << packageName << "\n\n";
			return 0;
		}
	}
	catch (std::exception)
	{
		return 0;
	}
	return -1;
}