#include "InstallLib.h"


bool InstallLib::CreateInstallPkg(std::string PackageDesc, PackageDescriptor desc, std::string PackageOutput)
{
	struct archive *a;
	struct archive_entry *entry;
	struct stat st;
	char buff[8192];
	int len;
	int fd;
	
	try
	{
		a = archive_write_new();
		archive_write_add_filter_gzip(a);
		archive_write_set_format_pax_restricted(a);
		archive_write_open_filename(a, PackageOutput.c_str());
		desc.Files.push_back(File(PackageDesc));
		;
		for (int i = 0; i < desc.Files.size(); i++)
		{
			std::filesystem::path ifp = desc.Files[i].InputFile;
			std::string dest = desc.Files[i].GetFileDest();
			entry = archive_entry_new();
			archive_entry_set_pathname(entry, dest.c_str());
			archive_entry_set_size(entry, std::filesystem::file_size(ifp));
			archive_entry_set_filetype(entry, AE_IFREG);
			archive_entry_set_perm(entry, 0644);
			archive_write_header(a, entry);
		
			int fd = open(desc.Files[i].InputFile.c_str(), AE_IFREG);
			len = read(fd, buff, sizeof(buff));
			while (len > 0)
			{
				archive_write_data(a, buff, len);
				len = read(fd, buff, sizeof(buff));
			}
			close(fd);
		
			std::cout << "Added: " << ifp << " to the archive\n";
			archive_entry_free(entry);
		}
		archive_write_close(a);
		archive_write_free(a);
		std::cout << "Created package: " << PackageOutput << "\n";
	}
	catch (std::exception &e)
	{
		std::cout <<  "Exception, procesing failed.  Msg: " << e.what();
		return false;
	}
	
	return true;
}

bool InstallLib::unzipPackage(std::string PackageFile, std::string tmpDir)
{
#if ARCHIVE_VERSION_NUMBER >= 3000000
	int64_t offset;
#else
	off_t offset;
#endif
	try
	{
		struct archive *a;
		struct archive *ext;
		struct archive_entry *entry;
		int flags;
		int r;

		/* Select which attributes we want to restore. */
		flags = ARCHIVE_EXTRACT_TIME;
		flags |= ARCHIVE_EXTRACT_PERM;
		flags |= ARCHIVE_EXTRACT_ACL;
		flags |= ARCHIVE_EXTRACT_FFLAGS;

		a = archive_read_new();
		archive_read_support_format_all(a);
		archive_read_support_filter_all(a);
		ext = archive_write_disk_new();
		archive_write_disk_set_options(ext, flags);
		archive_write_disk_set_standard_lookup(ext);
		
		if ((r = archive_read_open_filename(a, PackageFile.c_str(), 10240)))
			return false;
		for (;;) {
			r = archive_read_next_header(a, &entry);
			const char* currentFile = archive_entry_pathname(entry);
			const std::string fullOutputPath = tmpDir + currentFile;
			archive_entry_set_pathname(entry, fullOutputPath.c_str());
			if (r == ARCHIVE_EOF)
				return false;
			if (r < ARCHIVE_OK)
				fprintf(stderr, "%s\n", archive_error_string(a));
			if (r < ARCHIVE_WARN)
				break;
			r = archive_write_header(ext, entry);
			if (r < ARCHIVE_OK)
				fprintf(stderr, "%s\n", archive_error_string(ext));
			else if (archive_entry_size(entry) > 0) {
				r = copy_data(a, ext);
				if (r < ARCHIVE_OK)
					fprintf(stderr, "%s\n", archive_error_string(ext));
				if (r < ARCHIVE_WARN)
					return false;
			}
			r = archive_write_finish_entry(ext);
			if (r < ARCHIVE_OK)
				fprintf(stderr, "%s\n", archive_error_string(ext));
			if (r < ARCHIVE_WARN)
				return false;
		}
		archive_read_close(a);
		archive_read_free(a);
		archive_write_close(ext);
		archive_write_free(ext);
		
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

int InstallLib::copy_data(struct archive *ar, struct archive *aw)
{
	int r;
	const void *buff;
	size_t size;
	la_int64_t offset;

	for (;;) {
		r = archive_read_data_block(ar, &buff, &size, &offset);
		if (r == ARCHIVE_EOF)
			return (ARCHIVE_OK);
		if (r < ARCHIVE_OK)
			return (r);
		r = archive_write_data_block(aw, buff, size, offset);
		if (r < ARCHIVE_OK) {
			fprintf(stderr, "%s\n", archive_error_string(aw));
			return (r);
		}
	}
}
bool InstallLib::InstallPackage(std::string PackageFile)
{
	if (!std::filesystem::exists(PackageFile))
	{
		std::cout << "Package: " << PackageFile << " does not exist or is not readable\n";
		return false;
	}
	std::filesystem::path tmpDir = std::filesystem::temp_directory_path();
	tmpDir /= mktemp("XXXXXX");
	std::filesystem::create_directory(tmpDir);
	bool res = unzipPackage(PackageFile, tmpDir);
	if (!res)
	{
		std::filesystem::remove_all(tmpDir);
		return false;
	}
	
	std::filesystem::path jsonFile(tmpDir);
	jsonFile /= "package.json";
	if (!std::filesystem::exists(jsonFile))
	{
		std::filesystem::remove_all(tmpDir);
		return false;
	}
	
	std::fstream istream("package.json");
	std::stringstream pjson;
	std::string line;
	while (getline(istream, line))
	{
		pjson << line << "\n";
	}
		
	
	PackageDescriptor desc;
	try
	{
		cJSON *json = cJSON_Parse(pjson.str().c_str());
		desc = PackageDescriptor::FromJSON(json);
	}
	catch (const std::exception&e)
	{
		std::cout << "Failed to parse package.json, " << e.what() << "\n\n";
		std::filesystem::remove_all(tmpDir);
		return false;
	}
	
	// Next step is to validate that this is a good install for this machine
	// 1. Right installation medium for the device
	// 2. It is a newer version
	
	// Then we will exec a shell script that will
	// 1. Shut down the service
	// 2. Copy the files over to the service dir
	// 3. Restart the service
	// 4. Clean up install detritus
	
}