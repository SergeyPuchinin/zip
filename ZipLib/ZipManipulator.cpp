#include "pch.h"
#include "ZipManipulator.h"
#include "zip.h"

#include <filesystem>

using namespace ZipLib;

ZipManipulator::~ZipManipulator()
{
	if (_opened)
		saveArchive();
}

bool ZipManipulator::createZipArchive(std::string path)
{
	_archive = zip_open(path.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
	if (!_archive)
	{
		_errorDescription = "Cannot create archive file.";
		return false;
	}
	_opened = true;
	return true;
}

int ZipManipulator::addFile(std::string path, std::string entity)
{
	int result = zip_entry_open(_archive, entity.c_str());
	if (result >= 0)
	{
		result = zip_entry_fwrite(_archive, path.c_str());
		if (result >= 0)
		{
			result = zip_entry_close(_archive);
		}
	}

	if (result < 0)
		_errorDescription = zip_strerror(result);

	return result;
}

int ZipManipulator::addFolder(std::string path, std::string entity)
{
	std::filesystem::path folderPath = path;
	int result = 0;

	if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path))
	{
		_errorDescription = "Folder not exist.";
		return -1000;
	}

	for (auto& f : std::filesystem::directory_iterator(folderPath))
	{
		if (f.is_directory())
		{
			std::string entityFolder = entity + f.path().filename().u8string() + "/";
			result = addFolder(f.path().u8string(), entityFolder);

			if (result < 0)
			{
				_errorDescription = zip_strerror(result);
				return result;
			}
		}
		else
		{			
			std::string entityFile = entity + f.path().filename().u8string();
			result = addFile(f.path().u8string(), entityFile);

			if (result < 0)
			{
				_errorDescription = zip_strerror(result);
				return result;
			}
		}
	}

	if (result < 0)
		_errorDescription = zip_strerror(result);

	return result;
}

void ZipManipulator::saveArchive()
{
	zip_close(_archive);
	_opened = false;
}

int ZipManipulator::unzipArchive(std::string zip, std::string destiny)
{
	int result = zip_extract(zip.c_str(), destiny.c_str(), NULL, NULL);
	if (result < 0)
		_errorDescription = zip_strerror(result);

	return result;
}