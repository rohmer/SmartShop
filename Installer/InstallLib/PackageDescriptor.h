#pragma once

#include <string>
#include <vector>
#include <cjson/cJSON.h>
#include "Version.h"
#include "File.h"

class PackageDescriptor
{
public:
	std::string PackageName, Description, SoftwareName, InstallDir;
	Version PackageVersion;
	std::vector<File> Files;
	
	PackageDescriptor()
	{
	}
	
	PackageDescriptor(std::string name, 
		std::string description, 
		std::string softwareName, 
		std::string installDir,
		Version version, 
		std::vector<File> files) :
		PackageName(name),
		Description(description),
		SoftwareName(softwareName),
		InstallDir(installDir),
		PackageVersion(version),
		Files(files)
	{
	}
	PackageDescriptor(std::string name, 
		std::string description, 
		std::string softwareName, 
		std::string installDir,
		Version version)
		: PackageName(name)
		, Description(description)
		, SoftwareName(softwareName)
		, InstallDir(installDir)
		, PackageVersion(version)
	{
	}
	
	cJSON *ToJSON()
	{
		cJSON *obj = cJSON_CreateObject();
		cJSON_AddStringToObject(obj, "name", PackageName.c_str());
		cJSON_AddStringToObject(obj, "desc", Description.c_str());
		cJSON_AddStringToObject(obj, "software", SoftwareName.c_str());
		cJSON_AddStringToObject(obj, "installDir", InstallDir.c_str());
		cJSON_AddItemToObject(obj, "version", PackageVersion.ToJSON());
		cJSON* files=cJSON_CreateArray();
		for (std::vector<File>::iterator it = Files.begin(); it != Files.end(); it++)
		{
			cJSON_AddItemToArray(files, it->ToJSON());
		}
		cJSON_AddItemToObject(obj, "files", files);
		
		return obj;
	}
	
	static PackageDescriptor FromJSON(cJSON *json)
	{
		std::string pname, sname, desc, dir;
		Version v;
		if (cJSON_HasObjectItem(json, "name"))
		{
			pname = cJSON_GetObjectItem(json, "name")->valuestring;
		}
		if (cJSON_HasObjectItem(json, "desc"))
		{
			desc = cJSON_GetObjectItem(json, "desc")->valuestring;
		}
		if (cJSON_HasObjectItem(json, "software"))
		{
			sname = cJSON_GetObjectItem(json, "software")->valuestring;
		}
		if (cJSON_HasObjectItem(json, "installDir"))
		{
			dir = cJSON_GetObjectItem(json, "installDir")->valuestring;
		}
		if (cJSON_HasObjectItem(json, "version"))
		{
			v = Version::FromJSON(cJSON_GetObjectItem(json, "version"));
		}
		
		PackageDescriptor ret(pname, desc, sname, dir, v);
		if (cJSON_HasObjectItem(json, "files"))
		{
			cJSON *fileArray = cJSON_GetObjectItem(json, "files");
			if (cJSON_IsArray(fileArray))
			{
				cJSON *file;
				cJSON_ArrayForEach(file, fileArray)
				{
					File f = File::FromJSON(file);
					ret.Files.push_back(f);
				}
			}
		}
		return ret;
	}
};