#pragma once

#include <iostream>
#include <string>
#include "../../Components/cxxopts-master/include/cxxopts.hpp"

class Options
{
public:
	static std::string packageName;
	
	static bool ParseOpts(int argc, char *argv[])
	{
		cxxopts::Options options("GenInstall", "Creates an installation bundle");
		options.add_options()
			("f,file", "The package file name, otherwise it will be software name", cxxopts::value<std::string>());
	
		auto result = options.parse(argc, argv);
	
		if (result.count("file") == 1)
		{
			packageName = result["file"].as<std::string>();
		}
		
		return true;
	}
};
