#include "pch.h"
#include "ZipManipulator.h"

#include<filesystem>

using namespace ZipLib;

TEST(ZipManipulator, CreateArchive) 
{
	std::string archivePath = "C:/Temp/test.zip";
	ZipManipulator* zip = new ZipManipulator();
	EXPECT_TRUE(zip->createZipArchive(archivePath));
	EXPECT_EQ(zip->addFolder("C:/Temp/Test/", ""), 0);
	zip->saveArchive();
	std::filesystem::exists(archivePath);
}

TEST(ZipManipulator, CreateArchiveFromNonExistFolder)
{
	ZipManipulator* zip = new ZipManipulator();
	EXPECT_TRUE(zip->createZipArchive("C:/Temp/test2.zip"));
	EXPECT_TRUE(zip->addFolder("C:/Temp/Testing", "")<0);
	zip->saveArchive();
}

TEST(ZipManipulator, ExtractArchive)
{
	ZipManipulator* zip = new ZipManipulator();
	EXPECT_EQ(zip->unzipArchive("C:/Temp/test.zip", "C:/Temp/Test2/"),0);
}

TEST(ZipManipulator, ExtractNonExistArchive)
{
	ZipManipulator* zip = new ZipManipulator();
	EXPECT_TRUE(zip->unzipArchive("C:/Temp/test1.zip", "C:/Temp/Test2/") < 0);
}