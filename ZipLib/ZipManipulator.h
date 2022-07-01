#pragma once
#include "DllExport.h"

#include <string>

struct zip_t;

namespace ZipLib
{
	class ZIPLIB_IMPEXP ZipManipulator
	{
	public:
		ZipManipulator() {};
		~ZipManipulator();

		/*Create new archive and open it to write.
		*
		@param path path to zip archive
		*
		@return true if archive was created successfully.
		*/
		bool createZipArchive(std::string path);

		/*Add file to archive
		*
		@param path path to file
		@param entity path to file in archive
		*
		@return the return code - 0 on success, negative number (< 0) on error.
		*/
		int addFile(std::string path, std::string entity);

		/*Add folder to archive
		*
		* If entity = "" then files from folder will be put to root of archive
		*
		@param path path to folder
		@param entity path to folder in archive.
		*
		@return the return code - 0 on success, negative number (< 0) on error.
		*/
		int addFolder(std::string path, std::string entity);

		/*Save archive to file and close it.
		After this function you cann't add anything to archive.
		*/
		void saveArchive();

		/*Extract data from archive
		*
		@param zip path to zip archive
		@param destiny path to output directory
		*
		@return the return code - 0 on success, negative number (< 0) on error.
		*/
		int unzipArchive(std::string zip, std::string destiny);

		/*Get description of last error code getted by any method
		*/
		std::string getErrorDescription() { return _errorDescription; }

	private:
		zip_t* _archive = NULL;
		std::string _errorDescription;
		bool	_opened;
	};

}