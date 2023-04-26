#include "FileDescriptor.h"

cJSON *FileDescriptor::ToJSON()
{
	cJSON *json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "SourceFile", cJSON_CreateString(SourceFile.c_str()));
	cJSON_AddItemToObject(json, "DestinationFolder", cJSON_CreateString(DestinationFolder.c_str()));
	cJSON_AddItemToObject(json, "MD5Hash", cJSON_CreateString(MD5Hash.c_str()));
	cJSON_AddItemToObject(json, "FileType", cJSON_CreateNumber((int)FileType));
	cJSON_AddItemToObject(json, "FileVersion", FileVersion.ToJSON());
	return json;
}

FileDescriptor FileDescriptor::FromJSON(cJSON *json)
{
	std::string src, dest, hash;
	eFileType ft;
	Version version(0, 0, 0);
	
	if (cJSON_HasObjectItem(json, "SourceFile"))
	{
		src = cJSON_GetObjectItem(json, "SourceFile")->valuestring;
	}
	if (cJSON_HasObjectItem(json, "DestinationFolder"))
	{
		dest = cJSON_GetObjectItem(json, "DestinationFolder")->valuestring;
	}
	if (cJSON_HasObjectItem(json, "MD5Hash"))
	{
		hash = cJSON_GetObjectItem(json, "MD5Hash")->valuestring;
	}
	if (cJSON_HasObjectItem(json, "FileType"))
	{
		ft = (eFileType)cJSON_GetObjectItem(json, "FileType")->valueint;
	}
	if (cJSON_HasObjectItem(json, "FileVersion"))
	{
		version = Version::FromJSON(cJSON_GetObjectItem(json, "FileVersion"));
	}
	return FileDescriptor(src, dest, ft, version, hash);
}