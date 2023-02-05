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