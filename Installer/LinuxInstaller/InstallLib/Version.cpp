#include "Version.h"

Version Version::FromFile(std::string file)
{
	if (!std::filesystem::exists(file))
	{
		std::stringstream ss;
		ss << "Version file: " << file << " does not exist";
		Logger::GetInstance()->LogW(ss.str());
		return Version();	
	}
	
	std::ifstream ifs(file);
	std::string content( (std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	
	cJSON *json=NULL;
	
	try
	{
		json = cJSON_Parse(content.c_str());
	}
	catch (std::exception e)
	{
		std::stringstream ss;
		ss << "Failed to parse Version from file: " << file << ", exception: " << e.what();
		Logger::GetInstance()->LogW(ss.str());
		return Version();
	}
	
	return FromJSON(json);
}

bool Version::ToFile(std::string file)
{
	cJSON *json = ToJSON();
	std::string jstr = cJSON_Print(json);
	cJSON_Delete(json);
	
	try
	{
		std::ofstream out(file);
		if (out.is_open())
		{
			out << jstr;
			out.close();
			return true;
		}
		std::stringstream ss;
		ss << "Failed to open: " << file << " for writing";
		Logger::GetInstance()->LogW(ss.str());
	}
	catch (const std::exception e)
	{
		std::stringstream ss;
		ss << "Failed to write: " << file << ", exception: " << e.what();
		Logger::GetInstance()->LogW(ss.str());
	}
	return false;
}

std::string Version::ToString()
{
	std::stringstream ss;
	ss << Major << "." << Minor << "." << BuildNumber;
	return ss.str();
}

cJSON *Version::ToJSON()
{
	cJSON *json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "Major", cJSON_CreateNumber(Major));
	cJSON_AddItemToObject(json, "Minor", cJSON_CreateNumber(Minor));
	cJSON_AddItemToObject(json, "BuildNumber", cJSON_CreateNumber(BuildNumber));
	return json;
}

Version Version::FromJSON(cJSON *json)
{
	uint major = 0, minor = 0, buildNum = 0;
	if (cJSON_HasObjectItem(json, "Major")) 
	{
		major = (uint)cJSON_GetObjectItem(json, "Major")->valueint;
	}
	if (cJSON_HasObjectItem(json, "Minor"))
	{
		minor = (uint)cJSON_GetObjectItem(json, "Minor")->valueint;
	}
	if (cJSON_HasObjectItem(json, "BuildNumber"))
	{
		buildNum = (uint)cJSON_GetObjectItem(json, "BuildNumber")->valueint;
	}
	return Version(major, minor, buildNum);
}
