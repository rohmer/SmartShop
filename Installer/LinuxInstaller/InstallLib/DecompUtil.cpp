#include "DecompUtil.h"

bool DecompUtil::DecompressZip(std::string zipFile, std::string destFolder)
{
	Logger *log = Logger::GetInstance();
	
	if (!std::filesystem::exists(zipFile))
	{
		std::stringstream ss;
		ss << "Compressed file: " << zipFile << " does not exist";
		log->LogC(ss.str());
		return false;
	}
	
	if (!std::filesystem::exists(destFolder) || !std::filesystem::is_directory(destFolder))
	{
		if (!std::filesystem::is_directory(destFolder))
		{
			std::stringstream ss;
			ss << "Destination folder: " << destFolder << " is not a directory";
			log->LogC(ss.str());
			return false;		
		}
		std::stringstream ss;
		ss << "Destination folder: " << destFolder << " does not exist";
		log->LogC(ss.str());
		return false;
	}
	
	int r;
	ssize_t size;

	struct archive *a = archive_read_new();
	archive_read_support_format_all(a);
	struct archive *ext = archive_write_disk_new();
	archive_write_disk_set_standard_lookup(ext);
	if ((r = archive_read_open_filename(a, zipFile.c_str(), 10240)))
	{
		std::stringstream ss;
		ss << "Failed to decompress file: " << zipFile << ", error: " << archive_error_string(a);
		log->LogC(ss.str());
		return false;
	}
	
	struct archive_entry *entry;
	
	for (;;)
	{
		r = archive_read_next_header(a, &entry);
		if (r == ARCHIVE_EOF)
			break;
		if (r < ARCHIVE_OK)
		{
			std::stringstream ss;
			ss << "Error processing compressed file: " << zipFile << ", error: " << archive_error_string(a);
			log->LogC(ss.str());
			archive_read_close(a);
			archive_read_free(a);
			return false;
		}
		const char* currentFile = archive_entry_pathname(entry);
		const std::string fullOutputPath = destFolder + "/" + currentFile;
		archive_entry_set_pathname(entry, fullOutputPath.c_str());
		r = archive_write_header(ext, entry);
		if (r < ARCHIVE_OK)
		{
			std::stringstream ss;
			ss << "Error processing compressed file: " << zipFile << ", error: " << archive_error_string(a);
			log->LogC(ss.str());
			archive_read_close(a);
			archive_read_free(a);
			archive_write_close(ext);
			archive_write_free(ext);
			return false;
		}
		else if(archive_entry_size(entry) > 0)
			{
				r = copy_data(log, a, ext);
				if (r < ARCHIVE_OK)
				{
					std::stringstream ss;
					ss << "Error processing compressed file: " << zipFile << ", error: " << archive_error_string(a);
					log->LogC(ss.str());
					archive_read_close(a);
					archive_read_free(a);
					archive_write_close(ext);
					archive_write_free(ext);
					return false;
				}
			}
		r = archive_write_finish_entry(ext);
		if (r < ARCHIVE_OK)
		{
			std::stringstream ss;
			ss << "Error processing compressed file: " << zipFile << ", error: " << archive_error_string(a);
			log->LogC(ss.str());
			archive_read_close(a);
			archive_read_free(a);
			archive_write_close(ext);
			archive_write_free(ext);
			return false;
		}
	}
	archive_read_close(a);
	archive_read_free(a);
	archive_write_close(ext);
	archive_write_free(ext);
	return true;	
}

int DecompUtil::copy_data(Logger *log, struct archive *ar, struct archive *aw)
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
			{
				std::stringstream ss;
				ss << "Error processing compressed file, error: " << archive_error_string(aw);
				log->LogC(ss.str());
				return (r);
			}
		}
	}
}