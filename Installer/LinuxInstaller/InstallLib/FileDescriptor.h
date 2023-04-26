#pragma once

#include <string>

#include <cJSON.h>
#include "Version.h"

enum eFileType
{
	SYSTEM=0,
	UI=1,
	DEVICE=2
};

struct FileDescriptor
{
public:
	FileDescriptor(
		std::string sourceFile, 
		std::string destinationFolder, 
		eFileType fileType=eFileType::SYSTEM,
		Version fileVersion=Version(0, 0, 0),
		std::string hash="")
		: SourceFile(sourceFile)
		, DestinationFolder(destinationFolder)
		, MD5Hash(hash)
		, FileType(fileType)
		, FileVersion(fileVersion)
	{
	}
	
	std::string SourceFile, DestinationFolder, MD5Hash;
	eFileType FileType;
	Version FileVersion;
	
	cJSON *ToJSON();
	static FileDescriptor FromJSON(cJSON *json);
};