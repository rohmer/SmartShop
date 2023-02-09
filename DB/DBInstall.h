#pragma once

#include <string>

class DBInstall
{
public:
	int ID;
	std::string softwareType;
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