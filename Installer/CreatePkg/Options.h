#pragma once

#include <string>
#include "../../Components/cxxopts-master/include/cxxopts.hpp"
#include "Version.h"

class Options
{
public:
	static std::string Name, Desc, InstallDir, SoftwareName;
	static Version Ver;
	
	static bool ParseOpts(int args, char *argv[])
	{
		cxxopts::Options options("CreatePkg", "Creates an install package descriptor");
		options.add_options()
			("n,name", "Package Name", cxxopts::value<std::string>())
			("d,desc", "Package Description", cxxopts::value<std::string>())
			("i,dir", "Installation Directory", cxxopts::value<std::string>())
			("s,software", "Software Name", cxxopts::value<std::string>()->default_value("server"))
			("v,version", "Version (1.0.0) format", cxxopts::value<std::string>()->default_value("1.0.0"));
		
		auto result = options.parse(args, argv);
		if (result.count("name") != 1)
		{
			std::cout << "Name is required\n\n";
			std::cout << options.help() << "\n";
			return false;
		}
		if (result.count("desc") != 1)
		{
			std::cout << "Description is required\n\n";
			std::cout << options.help() << "\n";
			return false;
		}
		if (result.count("dir") != 1)
		{
			std::cout << "Installation dir is required\n\n";
			std::cout << options.help() << "\n";
			return false;
		}
		
		Name = result["name"].as<std::string>();
		Desc = result["desc"].as<std::string>();
		InstallDir = result["dir"].as<std::string>();
		SoftwareName = result["software"].as<std::string>();
		
		std::string vstr = result["version"].as<std::string>();
		
		try
		{
			Ver = Version::FromString(vstr);
		}
		catch (const std::exception&)
		{
			std::cout << "Failed to parse version: " << vstr << "\n\n";
			std::cout << options.help() << "\n";
			return false;
		}
		return true;
	}
};