#pragma once
#include <vector>
#include <CppUnitTestFramework/TestContainer.h>
#include "Filesystem/Directory.h"
#include "SharedLibrary.h"
#include "MessageLogger.h"

using namespace darknessNight::CppUnitTestFramework;
using namespace darknessNight::Filesystem;
using namespace darknessNight::SharedLibrary;

namespace darknessNight {
	namespace TestsRunner {
		class TestDiscover {
			std::vector<TestSuitePtr> suites;
			const std::string dllVersionFuncName = "getTestLibVersion";
			const std::string dllFuncName = "getTestsFromDynamicTestsLibrary";
			std::shared_ptr<DynamicLibrary> dynamicLibrary = nullptr;
			std::shared_ptr<Directory> directory = nullptr;
			MessageLogger* logger=nullptr;
			int loadedTests = 0;
		public:
			TestDiscover(std::shared_ptr<Directory>,std::shared_ptr<DynamicLibrary>, MessageLogger&);
			virtual ~TestDiscover();
			virtual void findAll(std::vector<std::string> paths, std::vector<std::string> extensions);
			virtual void findInFile(std::string path);
			virtual std::vector<std::string> getSuitesNames();
			virtual std::vector<TestSuitePtr> getSuites();
			virtual std::vector<TestCasePtr> getTestsList();
			virtual void safeClear();
		protected:
			void logStartWork();
			void logEndWork();
			void searchLibraries(std::vector<std::string> &paths, std::string &pattern);
			void searchLibrariesInDir(std::shared_ptr<Directory> &directory, std::string & pattern);
			void logLibraryNotSupported(std::string path);
			void logLibraryLoaded(std::string path);
			bool isCorrectLibrary(std::string path);
			bool isCorrectLibVersion(std::string path);
			void getTestsIfLibraryIsCorrect(std::string path);
			void tryGetTests(std::string & path);
			std::string prepareSearchPattern(std::vector<std::string> &extensions);
			void addExtensionsToPattern(std::vector<std::string> & extensions, std::string &pattern);
			void deleteDotsAtBeginExt(std::string &ext);
		};
	}
}
