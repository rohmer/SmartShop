#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <cjson/cJSON.h>
#include "../../Components/md5-master/md5.h"

class File
{
public:
	enum eFileType
	{
		STANDARD,
		UI, 
		SERVICE,
		FONT
	};
	std::string  InputFile;
	eFileType FileType;
	
	std::string GetHash(bool regenerate=false)
	{
		if (hash.size() == 0 || regenerate==true)
		{
			if (std::filesystem::exists(InputFile))
			{
				std::FILE *file = std::fopen(InputFile.c_str(), "rb");
				hash = md5file(file);
				std::fclose(file);				
			}
		}
		return hash;
	}
	
	File(std::string inputFile, eFileType fileType = eFileType::STANDARD) :
		InputFile(inputFile),
		FileType(fileType)
	{
		if (fileType == eFileType::UI)
		{
			std::filesystem::path path;
			path += "UI";
			
			path /= path.filename();
			filename = path;
		} else 
		if (fileType == eFileType::FONT)
		{
			std::filesystem::path path;
			path += "fonts";
			path /= path.filename();
			filename = path;
		}
		else
		{
			std::filesystem::path path = InputFile;
			filename = path.filename();
		}
	}
	
	File(std::string inputFile, eFileType fileType, std::string hash, std::string dest):
		InputFile(inputFile),
		FileType(fileType),
		hash(hash),
		filename(dest)		
	{
	}
	
	std::string GetFileDest()
	{
		return filename;
	}
	
	cJSON *ToJSON()
	{
		cJSON *obj = cJSON_CreateObject();
		cJSON_AddItemToObject(obj, "input", cJSON_CreateString(InputFile.c_str()));
		cJSON_AddItemToObject(obj, "dest", cJSON_CreateString(filename.c_str()));
		cJSON_AddItemToObject(obj, "hash", cJSON_CreateString(GetHash().c_str()));
		cJSON_AddItemToObject(obj, "type", cJSON_CreateNumber(FileType));
		return obj;
	}
	
	static File FromJSON(cJSON *json)
	{
		std::string input="", dest="", md5="";
		eFileType fileType = eFileType::STANDARD;
		std::string hash = "";
		if (cJSON_HasObjectItem(json,"input"))
		{
			input = cJSON_GetObjectItem(json, "input")->valuestring;
		}
		if (cJSON_HasObjectItem(json, "dest"))
		{
			dest = cJSON_GetObjectItem(json, "dest")->valuestring;
		}
		if (cJSON_HasObjectItem(json, "hash"))
		{
			hash = cJSON_GetObjectItem(json, "hash")->valuestring;
		}
		if (cJSON_HasObjectItem(json, "type"))
		{
			fileType = (eFileType)cJSON_GetObjectItem(json, "type")->valueint;
		}
		
		return File(input, fileType, hash, dest);
	}
	
private:
	std::string hash="";
	std::string filename;
};