#pragma once

#include <string>

class DBInstall
{
public:
	int ID;
	std::string packageName, packageDescription, packageFile;
	int major, minor, buildNum;
};

class DBInstallFile
{
public:
	int ID;
	int softwareID;
	std::string file;
	std::string checksum;
};