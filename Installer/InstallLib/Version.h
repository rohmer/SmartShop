#pragma once

#include <sstream>
#include <iostream>
#include <string>
#include <cjson/cJSON.h>

class Version
{
public:
	uint Major, Minor, BuildNum;
	
	Version(uint major = 0, uint minor = 0, uint buildNum = 0)
		: Major(major)
		, Minor(minor)
		, BuildNum(buildNum)
	{
	}
	
	cJSON *ToJSON()
	{
		cJSON *obj = cJSON_CreateObject();
		cJSON_AddItemToObject(obj, "major", cJSON_CreateNumber(Major));
		cJSON_AddItemToObject(obj, "minor", cJSON_CreateNumber(Minor));
		cJSON_AddItemToObject(obj, "build", cJSON_CreateNumber(BuildNum));
		return obj;
	}
	
	static Version FromJSON(cJSON *obj)
	{
		uint maj = 0, min = 0, build = 0;
		if (cJSON_HasObjectItem(obj, "major"))
		{
			maj = cJSON_GetObjectItem(obj, "major")->valueint;
		}
		if (cJSON_HasObjectItem(obj, "minor"))
		{
			min = cJSON_GetObjectItem(obj, "minor")->valueint;
		}
		if (cJSON_HasObjectItem(obj, "build"))
		{
			build = cJSON_GetObjectItem(obj, "build")->valueint;
		}
		return Version(maj, min, build);
	}
	
	static Version FromString(std::string vstr)
	{
		uint maj = 0, min = 0, build = 0, ctr = 0;
		std::istringstream ss(vstr);
		std::string s;
		while (getline(ss, s, '.') && ctr<3)
		{
			if (ctr == 0)
				maj = std::atoi(s.c_str());
			if (ctr == 1)
				min = std::atoi(s.c_str());
			if (ctr == 2)
				build = std::atoi(s.c_str());
			ctr++;
		}
		
		return Version(maj, min, build);
	}
		
};