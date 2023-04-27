#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <openssl/md5.h>

#include <cJSON.h>

#include "../../../Logger/Logger.h"
#include "../../../DB/DB.h"
#include "../../../DB/DBInstall.h"
#include "../../../Server/Settings.h"
#include "DecompUtil.h"
#include "PacakgeDescriptor.h"

class InstallLib
{
public:
	enum eInstallStage
	{
		START = 0,
		DECOMPRESS = 1,
		LOADPACKAGE = 2,
		CHECKSUM = 3,
		BACKUP = 4,
		STOP = 5,
		COPY = 6,
		RESTART = 7,
		STORE_TO_DB = 8,
		CLEANUP = 0
	};
	
	struct sInstallLog
	{
	public:
		sInstallLog(std::string msg, bool result)
			: LogMsg(msg)
			, Result(result)
		{
		}
		
		std::string LogMsg;
		bool Result;
	};
	
	
	static bool InstallPackage(std::string packageFile);
	
private:
	static bool decompressPacakge(std::string packageFile, std::string workingDir);
	
	static std::vector<sInstallLog> installLog;
	static bool installInProgress;
	static std::string randomStrGen(int length);
	
	static void cleanup(std::string packageFile, std::string workingDir);
	static bool storeToDB(std::string workingDir, PackageDescriptor &package, std::string packageFile);
	
	static bool uninstall(std::string workingDir, PackageDescriptor package, eInstallStage currentStage);
	
	static bool loadPackage(std::string workingDir, PackageDescriptor &package);
	
	static bool checkChecksums(std::string workingDir, PackageDescriptor &package);
	
	static bool backupFiles(std::string workingDir, PackageDescriptor &package);
	
	static bool copyFiles(std::string workingDir, PackageDescriptor &package);
	
	static bool stop(std::string workingDir, PackageDescriptor &package);
	
	static bool start(std::string workingDir, PackageDescriptor &package);
	
	
	static std::string getFileChecksum(std::string file);
	
	
};
