#include <filesystem>
#include <fstream>
#include <iostream>

#include <cjson/cJSON.h>

#include "Options.h"
#include "File.h"
#include "PackageDescriptor.h"

using namespace std;

std::string Options::file, Options::fileWildcard;
bool Options::isRecursive, Options::isUI, Options::isService, Options::isFont;

PackageDescriptor AddFile(std::string file, PackageDescriptor desc, bool isUI, bool isService=false, bool isFont=false)
{
	std::vector<File> files;
	bool found = false;
	for (std::vector<File>::iterator it = desc.Files.begin(); it != desc.Files.end(); ++it)
	{
		if (strcmp(it->InputFile.c_str(), file.c_str()) != 0)
		{
			files.push_back(*it);
		}
		else
		{
			found = true;
		}
	}

	if (found)
		std::cout << "Updating file: " << file << "\n";
	else
		std::cout << "Adding file: " << file << "\n";
	
	desc.Files.clear();
	
	File::eFileType ft = File::STANDARD;
	if (isUI)
		ft = File::UI;
	if (isService)
		ft = File::SERVICE;
	if (isFont)
		ft = File::FONT;
	File f(file, ft);
	files.push_back(f);
	for (std::vector<File>::iterator it = files.begin(); it != files.end(); ++it)
	{
		desc.Files.push_back(*it);
	}
	return desc;
}

PackageDescriptor AddWildcard(std::string wildcard, bool Recursive, PackageDescriptor desc, bool isUI, bool isFont)
{
	std::vector<std::string> fileList;
	try
	{	
		if (Recursive)
		{
			std::filesystem::path p = std::filesystem::current_path();
			for (const std::filesystem::directory_entry &entry : std::filesystem::recursive_directory_iterator(p))
			{
				if (entry.path().has_extension() && !entry.is_directory())
				{
					std::string ext = entry.path().extension();	
					std::string extNoDot = entry.path().extension().string().substr(1, std::string::npos);
					if (strcmp(ext.c_str(),wildcard.c_str()) == 0 ||
						strcmp(extNoDot.c_str(), wildcard.c_str()) == 0)
						fileList.push_back(entry.path());
				}
			}
		}
		else
		{
			std::filesystem::path p = std::filesystem::current_path();
			;	
			for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(p))
			{
				if (entry.path().has_extension() && !entry.is_directory())
				{
					std::string ext = entry.path().extension();	
					std::string extNoDot = entry.path().extension().string().substr(1, std::string::npos);
					if (strcmp(ext.c_str(), entry.path().extension().c_str()) == 0 ||
						strcmp(extNoDot.c_str(), entry.path().extension().c_str()) == 0)
						fileList.push_back(entry.path());
				}
			}
		}
	}
	catch (std::exception &e)
	{
		std::cout << "Exception adding files: " << e.what() << "\n\n";
	}
	for (std::vector<std::string>::iterator it = fileList.begin(); it != fileList.end(); ++it)
	{
		desc = AddFile(*it, desc, isUI);
	}
	return desc;
}

int main(int argc, char *argv[])
{
	if (!Options::ParseOpts(argc, argv))
	{
		return -1;
	}
	
	if (!std::filesystem::exists("package.json"))
	{
		std::cout << "package.json file missing, generate one using CreatePkg\n\n";
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
	
	
	if (Options::file.length() > 0)
	{
		desc=AddFile(Options::file, desc, Options::isUI, Options::isService, Options::isFont);
	}
	
	if (Options::fileWildcard.length() > 0)
	{
		desc = AddWildcard(Options::fileWildcard, Options::isRecursive, desc, Options::isUI, Options::isFont);
	}
	
	try
	{
		cJSON *json = desc.ToJSON();
		std::ofstream file;
		file.open("package.json", _S_out);
	
		file << cJSON_Print(json);
		file.close();		
	}
	catch (const std::exception&e)
	{
		std::cout << "Error writing manifest, " << e.what() << "\n\n";
		return -1;
	}
}

