#include "InstallLib.h"

bool InstallLib::installInProgress = false;
std::vector<InstallLib::sInstallLog> InstallLib::installLog;

bool InstallLib::InstallPackage(std::string packageFile)
{
	srand(time(NULL));
	
	if (installInProgress)
	{
		Logger::GetInstance()->LogW("Install in progress, try again later");
		return false;
	}
	installLog.clear();
	
	std::filesystem::path workingDir = std::filesystem::temp_directory_path();
	workingDir /= randomStrGen(8);
	eInstallStage currentStage = eInstallStage::DECOMPRESS;
	PackageDescriptor packageDescriptor;
	bool result;
	
	try
	{
		result = decompressPacakge(packageFile, workingDir);
	}
	catch (std::exception e)
	{
		std::stringstream ss;
		ss << "Error decompressing package, " << e.what();
		installLog.push_back(sInstallLog(ss.str(), false));
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;
	}
	
	if (!result)
	{
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;
	}
	currentStage = eInstallStage::LOADPACKAGE;
	
	try
	{
		result = loadPackage(workingDir, packageDescriptor);	
	}
	catch (const std::exception &e)
	{
		std::stringstream ss;
		ss << "Error decompressing package, " << e.what();
		installLog.push_back(sInstallLog(ss.str(), false));
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;
	}
	
	if (!result)
	{
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;
	}
	
}

bool InstallLib::decompressPacakge(std::string package, std::string workingDir)
{
	if (!DecompUtil::DecompressZip(package, workingDir))
	{
		installLog.push_back(sInstallLog("Failed to decompress pacakge", false));
		return false;
	}
	installLog.push_back(sInstallLog("Decompressed pacakge", true));
	return true;
}

bool InstallLib::loadPackage(std::string workingDir, PackageDescriptor &package)
{
	std::filesystem::path p = workingDir;
	p /= "package.json";
	
	if (!std::filesystem::exists(p))
	{
		installLog.push_back(sInstallLog("Could not load package descriptor", false));
		return false;
	}

	std::ifstream ifs(p.string());
	std::string content( (std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	
	cJSON *json = cJSON_Parse(content.c_str());
	package = PackageDescriptor::FromJSON(json);
	cJSON_Delete(json);
	installLog.push_back(sInstallLog("Loaded package descriptor", false));
	return true;
}

bool InstallLib::checkChecksums(std::string workingDir, PackageDescriptor &package)
{
	bool error = false;
	for (std::vector<FileDescriptor>::iterator it = package.PackageFiles.begin();
		it != package.PackageFiles.end();
		++it)
	{
		std::filesystem::path p=workingDir;
		if (it->DestinationFolder.length() > 0)
			p /= it->DestinationFolder;
		p /= it->SourceFile;
		if (std::strcmp(getFileChecksum(p.string()).c_str(), it->MD5Hash.c_str()) != 0)
		{
			std::stringstream ss;
			ss << "Failed checkum check on: " << it->SourceFile;
			installLog.push_back(sInstallLog(ss.str(), false));
			error = true;
		}
	}
	if (!error)
	{
		return false;
	}
	return true;
}
	
std::string InstallLib::getFileChecksum(std::string file)
{
	std::ifstream ifile(file,std::ifstream::binary);
	MD5_CTX md5Context;
	MD5_Init(&md5Context);
	char buf[1024 * 16];
	while (ifile.good()) {
		ifile.read(buf, sizeof(buf));
		MD5_Update(&md5Context, buf, ifile.gcount());
	}
	unsigned char result[MD5_DIGEST_LENGTH];
	MD5_Final(result, &md5Context);
		
	std::stringstream md5string;
	md5string << std::hex;
	for (const auto &byte : result)
		md5string << (int)byte;
	return md5string.str();
}

std::string InstallLib::randomStrGen(int length) {
	static std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	std::string result;
	result.resize(length);

	for (int i = 0; i < length; i++)
		result[i] = charset[rand() % charset.length()];

	return result;
}
