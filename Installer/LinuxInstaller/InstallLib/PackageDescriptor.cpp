#include "PacakgeDescriptor.h"

PackageDescriptor PackageDescriptor::FromJSON(cJSON *json)
{
	std::string name, desc;
	Version version(0, 0, 0);
	std::vector<FileDescriptor> files;
	
	if (cJSON_HasObjectItem(json, "PackageName"))
		name = cJSON_GetObjectItem(json, "PackageName")->valuestring;
	if (cJSON_HasObjectItem(json, "PackageDescription"))
		desc = cJSON_GetObjectItem(json, "PackageDescription")->valuestring;
	if (cJSON_HasObjectItem(json, "PackageVersion"))
		version = Version::FromJSON(cJSON_GetObjectItem(json, "PackageVersion"));
	if (cJSON_HasObjectItem(json, "PackageFiles"))
	{
		cJSON *pf = cJSON_GetObjectItem(json, "PackageFiles");
		if (cJSON_IsArray(pf))
		{
			cJSON *itr;
			cJSON_ArrayForEach(itr, pf)
			{
				files.push_back(FileDescriptor::FromJSON(itr));
			}
		}
		else
		{
			Logger::GetInstance()->LogC("PackageFiles is not an array, package is malformed");
		}
	}
	return PackageDescriptor(name, desc, version, files);
}

cJSON *PackageDescriptor::ToJSON()
{
	cJSON *json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "PackageName", cJSON_CreateString(PackageName.c_str()));
	cJSON_AddItemToObject(json, "PackageDescription", cJSON_CreateString(PackageName.c_str()));
	cJSON_AddItemToObject(json, "PackageVersion", PackageVersion.ToJSON());
	
	cJSON *fileArray = cJSON_CreateArray();
	for(int i=0; i<PackageFiles.size(); i++)
	{
		cJSON_AddItemToArray(fileArray, PackageFiles[i].ToJSON());
	}
	cJSON_AddItemToObject(fileArray, "PackageFiles", fileArray);
	return json;
}