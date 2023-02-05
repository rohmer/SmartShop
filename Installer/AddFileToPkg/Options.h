#pragma once

#include <iostream>
#include <string>
#include "../../Components/cxxopts-master/include/cxxopts.hpp"

class Options
{
public:
	static std::string file, fileWildcard;
	static bool isRecursive, isUI, isService, isFont;
	static bool ParseOpts(int argc, char *argv[])
	{
		cxxopts::Options options("AddFileToPkg", "Adds file(s) to a package.json file");
		options.add_options()
			("f,file", "File Name", cxxopts::value<std::string>())
			("e,extension", "Get all files of a certain extension", cxxopts::value<std::string>())
			("r,recursive", "Extension is recursive", cxxopts::value<bool>())
			("u,ui", "File(s) are UI", cxxopts::value<bool>())
			("n,font", "File(s) are fonts", cxxopts::value<bool>())
			("s,service", "File is the service file", cxxopts::value<bool>());
		
		auto result = options.parse(argc, argv);
		if (result.count("file") != 1 && result.count("extension") != 1)
		{
			std::cout << "You must have ONE file or wildcard\n\n";
			std::cout << options.help() << "\n\n";
			return false;
		}
		
		if(result.count("file")==1)
			file = result["file"].as<std::string>();
		if(result.count("extension")==1)
			fileWildcard = result["extension"].as<std::string>();
		if (result.count("recursive")== 1)
			isRecursive = true;
		else
		{
			isRecursive = false;
		}
		if (result.count("ui") == 1)
			isUI = true;
		else
		{
			isUI = false;
		}
		
		if (result.count("service") == 1)
		{
			isService = true;
		}
		if (result.count("font") == 1)
		{
			isFont = true;
		}
		if (isService&&isRecursive)
		{
			std::cout << "Service and Recursive cannot be used together";
			std::cout << options.help() << "\n\n";
			return false;
		}

		return true;
		
			
	}
};