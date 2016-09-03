#include "stdafx.h"
#include "../TestsRunner/Filesystem/Directory.h"
#include <direct.h>
#include <time.h>
#include <regex>

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
		_mkdir("TestDir/RecN");
		_mkdir("TestDir/RecN/NotUse");
		_mkdir("TestDir/Dir1/Rec1");
		_mkdir("TestDir/Dir1/Rec2");
		createDirTimeMax = time(nullptr) + 1;
	}
	TEST_METHOD_CLEANUP(TearDown) {
		_rmdir("TestDir/Dir1/Rec1");
		_rmdir("TestDir/Dir1/Rec2");
		_rmdir("TestDir/RecN/NotUse");
		_rmdir("TestDir/Dir1");
		_rmdir("TestDir/Dir2");
		_rmdir("TestDir/DirN");
		_rmdir("TestDir/RecN");
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

		Assert::AreEqual(6,count);
		Assert::AreEqual(3, dirNamedCount);
	}

	TEST_METHOD(IterDirRec_HasCorrectDir_CheckReturnAllDirs) {
		int count = 0;
		int dirNamedCount = 0;
		int recNamedCount = 0;

		Directory dir("./TestDir");
		sumFindedFiles(dir, count, dirNamedCount, recNamedCount);

		assertFindedFilesCounts(count, dirNamedCount, recNamedCount);
	}

	void assertFindedFilesCounts(int &count, int &dirNamedCount, int &recNamedCount) {
		Assert::AreEqual(23, count);
		Assert::AreEqual(3, dirNamedCount);
		Assert::AreEqual(3, recNamedCount);
	}

	void sumFindedFiles(darknessNight::Filesystem::Directory &dir, int &count, int &dirNamedCount, int &recNamedCount) {
		for (auto subdir = dir.recursiveBegin(); subdir != dir.recursiveEnd(); subdir++) {
			count++;
			sumDirNamedFiles(subdir, dirNamedCount);
			sumRecNamedFiles(subdir, recNamedCount);
		}
	}

	void sumRecNamedFiles(darknessNight::Filesystem::DirRecursiveIterator &subdir, int & recNamedCount) {
		std::regex recNamed(".*\\/Rec.$");
		if (std::regex_match(subdir->getPath(), recNamed))
			recNamedCount++;
	}

	void sumDirNamedFiles(darknessNight::Filesystem::DirRecursiveIterator &subdir, int & dirNamedCount) {
		std::regex dirNamed(".*\\/Dir.$");
		if (std::regex_match(subdir->getPath(), dirNamed))
			dirNamedCount++;
	}


	TEST_METHOD(IterDirSearch_HasCorrectDir_CheckReturnAllPatternDirs) {
		int count = 0;
		int dirNamedCount = 0;
		countSearchedDirs(count, dirNamedCount);
		AssertSearchIter(count, dirNamedCount);
	}

	void AssertSearchIter(int &count, int &dirNamedCount) {
		Assert::AreEqual(3, count);
		Assert::AreEqual(3, dirNamedCount);
	}

	void countSearchedDirs(int &count, int &dirNamedCount) {
		Directory dir("./TestDir");
		std::regex reg(".*/Dir.$");
		for (auto subdir = dir.searchBegin(".*/Dir.$"); subdir != dir.searchEnd(); subdir++) {
			count++;
			if (std::regex_match(subdir->getPath(), reg))
				dirNamedCount++;
		}
	}


			};
		}
	}
}