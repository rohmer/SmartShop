#pragma once

#include <string>

class DBInstall
{
public:
	unsigned int ID;
	std::string packageName, packageDescription, packageFile;
	int major, minor, buildNum;
	time_t installTime;
};

class DBInstallFile
{
public:
	unsigned int ID;
	int softwareID;
	std::string file;	// This includes the path
	std::string checksum;
	int major, minor, buildNum;
	time_t installTime;
	
};