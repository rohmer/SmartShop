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
	currentStage = eInstallStage::CHECKSUM;
	
	try
	{
		result = checkChecksums(workingDir, packageDescriptor);
	}
	catch (const std::exception &e)
	{
		std::stringstream ss;
		ss << "Error evaluating checksums in package, " << e.what();
		installLog.push_back(sInstallLog(ss.str(), false));
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;		
	}
	if (!result)
	{
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;
	}
	
	try
	{
		result = backupFiles(workingDir, packageDescriptor);
	}
	catch (const std::exception &e)
	{
		std::stringstream ss;
		ss << "Error backing up files in package, " << e.what();
		installLog.push_back(sInstallLog(ss.str(), false));
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;		
	}
	if (!result)
	{
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;
	}
	
	currentStage = eInstallStage::STOP;
	try
	{
		result = stop(workingDir, packageDescriptor);
	}
	catch (const std::exception &e)
	{
		std::stringstream ss;
		ss << "Error stopping SmartShop, " << e.what();
		installLog.push_back(sInstallLog(ss.str(), false));
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;		
	}
	if (!result)
	{
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;
	}
	
	currentStage = eInstallStage::COPY;
	try
	{
		result = copyFiles(workingDir, packageDescriptor);
	}
	catch (const std::exception &e)
	{
		std::stringstream ss;
		ss << "Error copying files in package, " << e.what();
		installLog.push_back(sInstallLog(ss.str(), false));
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;		
	}
	if (!result)
	{
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;
	}
	
	currentStage = eInstallStage::RESTART;
	try
	{
		result = start(workingDir, packageDescriptor);
	}
	catch (const std::exception &e)
	{
		std::stringstream ss;
		ss << "Error starting server, " << e.what();
		installLog.push_back(sInstallLog(ss.str(), false));
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;		
	}
	if (!result)
	{
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;
	}
	
	currentStage = eInstallStage::STORE_TO_DB;
	try
	{
		result = storeToDB(workingDir, packageDescriptor, packageFile);
	}
	catch (const std::exception &e)
	{
		std::stringstream ss;
		ss << "Error starting server, " << e.what();
		installLog.push_back(sInstallLog(ss.str(), false));
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;		
	}
	if (!result)
	{
		uninstall(workingDir, packageDescriptor, currentStage);
		return false;
	}
	
	currentStage = eInstallStage::CLEANUP;
	try
	{
		result = storeToDB(workingDir, packageDescriptor, packageFile);
	}
	catch (const std::exception &e)
	{
		std::stringstream ss;
		ss << "Error starting server, " << e.what();
		installLog.push_back(sInstallLog(ss.str(), false));
	}
	if (!result)
	{
		return false;
	}
	return true;
}

bool InstallLib::storeToDB(std::string workingDir, PackageDescriptor &package, std::string packageFile)
{
	DBInstall installRec;
	installRec.buildNum = package.PackageVersion.BuildNumber;
	installRec.installTime = std::time(NULL);
	installRec.major = package.PackageVersion.Major;
	installRec.minor = package.PackageVersion.Minor;
	installRec.packageDescription = package.PackageDescription;
	installRec.packageFile = packageFile;
	installRec.packageName = package.PackageName;
	installRec.ID = DB::GetInstance()->GetStorage()->insert(installRec);
	
	for (std::vector<FileDescriptor>::iterator it = package.PackageFiles.begin();
		it != package.PackageFiles.end();
		++it)
	{
		DBInstallFile fRec;
		fRec.buildNum = it->FileVersion.BuildNumber;
		fRec.checksum = it->MD5Hash;
		
		std::filesystem::path p = INSTALLDIR;
		p /= it->DestinationFolder;
		p /= it->SourceFile;
		fRec.file = p.string();
		fRec.installTime = installRec.installTime;
		fRec.major = it->FileVersion.Major;
		fRec.minor = it->FileVersion.Minor;
		
		// TODO: What am I gonna do about Software ID..
		fRec.ID = DB::GetInstance()->GetStorage()->insert(fRec);
	}
	installLog.push_back(sInstallLog("Stored package to DB", true));
	return true;
}

bool InstallLib::stop(std::string workingDir, PackageDescriptor &package)
{
	//TODO: When I actually figure out exactly how we will be managed
	return true;
}

bool InstallLib::start(std::string workingDir, PackageDescriptor &package)
{
	//TODO: When I actually figure out exactly how we will be managed
	return true;
}

bool InstallLib::copyFiles(std::string workingDir, PackageDescriptor &package)
{
	for (std::vector<FileDescriptor>::iterator it = package.PackageFiles.begin();
		it != package.PackageFiles.end();
		++it)
	{
		std::filesystem::path dest = INSTALLDIR; 
	    dest /= it->DestinationFolder;
		dest /= it->SourceFile;
		std::filesystem::path source = workingDir;
		source /= it->DestinationFolder;
		source /= it->SourceFile;
		
		try
		{
			std::filesystem::copy_file(source.string(),
				dest.string(),
				std::filesystem::copy_options::skip_existing  |
				std::filesystem::copy_options::copy_symlinks);
			std::stringstream ss;
			ss << "Copied file from: " << source.string() << " to dest: " << dest.string();
			installLog.push_back(sInstallLog(ss.str(), true));
		}
		catch (const std::exception &e)
		{
			std::stringstream ss;
			ss << "Failed to copy file from: " << source.string() << " to dest: " << dest.string() << ", error: "<<e.what();
			installLog.push_back(sInstallLog(ss.str(), false));
			return false;
		}
	}
	return true;
}

bool InstallLib::backupFiles(std::string workingDir, PackageDescriptor &package)
{
	for (std::vector<FileDescriptor>::iterator it = package.PackageFiles.begin();
		it != package.PackageFiles.end();
		++it)
	{
		std::filesystem::path p = INSTALLDIR; 
		p /= it->DestinationFolder;
		p /= it->SourceFile;
		
		using namespace sqlite_orm;
		std::vector<DBInstallFile> copies = DB::GetInstance()->GetStorage()->get_all<DBInstallFile>
			(
				where(c(&DBInstallFile::file) == p.string()),
				order_by(&DBInstallFile::installTime).desc()
			);
		for (std::vector<DBInstallFile>::iterator fit = copies.begin();
			fit != copies.end();
			++fit)
		{
			if (std::filesystem::exists(fit->file))
			{
				std::stringstream filePath;
				filePath << fit-> file << "." << fit->major << fit->minor << fit->buildNum;
				if (std::filesystem::exists(filePath.str()))
				{
					std::stringstream ss;
					ss << filePath.str() << " already exists, not backing up";
					installLog.push_back(sInstallLog(ss.str(), true));
				}
				else
				{
					try
					{
						std::filesystem::copy(fit->file, filePath.str(),
							std::filesystem::copy_options::skip_existing  |
							std::filesystem::copy_options::copy_symlinks);
						std::stringstream ss;
						ss << filePath.str() << " backed up";
						installLog.push_back(sInstallLog(ss.str(), true));
					}
					catch (const std::exception &e)
					{
						std::stringstream ss;
						ss << "Error backing up: " << filePath.str() << ", error: " << e.what();
						installLog.push_back(sInstallLog(ss.str(), false));
						return false;
					}
				}
			}
		}
	}
	return true;
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

bool InstallLib::uninstall(std::string workingDir, PackageDescriptor package, eInstallStage currentStage)
{ 
	//DO everthing backwards :)
}