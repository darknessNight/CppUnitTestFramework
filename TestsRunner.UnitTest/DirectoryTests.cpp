#include "stdafx.h"
#include "../TestsRunner/Filesystem/Directory.h"
#include <direct.h>
#include <time.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {
	namespace Filesystem {
		namespace IntegrationTests {
			TEST_CLASS(DirectoryTests) {
private:
	std::string currDir;
	unsigned long createDirTimeMin;
	unsigned long createDirTimeMax;
public:
	TEST_METHOD_INITIALIZE(SetUp) {
		char buff[1000];
		_getcwd(buff, 1000);
		currDir = buff;
		createDirTimeMin = time(nullptr) - 1;
		_mkdir("TestDir");
		_mkdir("TestDir/Dir1");
		_mkdir("TestDir/Dir2");
		_mkdir("TestDir/DirN");
		_mkdir("TestDir/Dir1/Rec1");
		_mkdir("TestDir/Dir1/Rec2");
		createDirTimeMax = time(nullptr) + 1;
	}

	TEST_METHOD_CLEANUP(TearDown) {
		_rmdir("TestDir/Dir1/Rec1");
		_rmdir("TestDir/Dir1/Rec2");
		_rmdir("TestDir/Dir1");
		_rmdir("TestDir/Dir2");
		_rmdir("TestDir/DirN");
		_rmdir("TestDir");
	}

	TEST_METHOD(GetCurrentDirectory_CheckReturnCorrectDir) {
		Directory dir = Directory::Current();
		std::string path = dir.getPath();
		Assert::AreEqual(currDir, path);
	}

	TEST_METHOD(OpenDir_HasCorrectDir_CheckNoThrow) {
		try {
			Directory dir("./TestDir");
		}
		catch (...) {
			Assert::Fail();
		}
	}

	TEST_METHOD(OpenDir_HasInCorrectDir_CheckThrow) {
		try {
			Directory dir("./UnExistsDir");
			Assert::Fail();
		}
		catch (FilesystemException ex) {
			Assert::AreEqual(std::string("Path is not exists"), ex.getMessage());
		}
	}

	TEST_METHOD(OpenDir_HasCorrectDir_CheckHasDates) {
		try {
			Directory dir("./TestDir");
			Assert::IsTrue(dir.getModificationTime() >= createDirTimeMin && dir.getModificationTime() <= createDirTimeMax);
			Assert::IsTrue(dir.getCreateTime() >= createDirTimeMin && dir.getCreateTime() <= createDirTimeMax);
			Assert::IsTrue(dir.getLastAccessTime() >= createDirTimeMin && dir.getLastAccessTime() <= createDirTimeMax);
		}
		catch (...) {
			Assert::Fail();
		}
	}

	TEST_METHOD(IterDir_HasCorrectDir_CheckReturnAllDirs) {
		int count = 0;
		int dirNamedCount = 0;
		Directory dir("./TestDir");
		for (auto subdir : dir) {
			count++;
			if ((int)subdir.getPath().find("/Dir") >= 0)
				dirNamedCount++;
		}

		Assert::AreEqual(5,count);
		Assert::AreEqual(3, dirNamedCount);
	}

	TEST_METHOD(IterDirRec_HasCorrectDir_CheckReturnAllDirs) {
		int count = 0;
		int dirNamedCount = 0;
		int recNamedCount = ;
		Directory dir("./TestDir");
		for (auto subdir = dir.recursiveBegin(); subdir != dir.recursiveEnd();subdir++) {
			count++;
			if ((int)subdir->getPath().find("/Dir") >= 0)
				dirNamedCount++;
			if ((int)subdir->getPath().find("/Rec") >= 0)
				recNamedCount++;
		}

		Assert::AreEqual(7, count);
		Assert::AreEqual(3, dirNamedCount);
		Assert::AreEqual(2, recNamedCount);
	}




			};
		}
	}
}