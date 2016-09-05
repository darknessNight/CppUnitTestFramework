#pragma once
#include <vector>
#include <string>
#include <CppUnitTestFramework/TestContainer.h>
#include <DependencyContainer/DependencyContainer.h>
#include "Filesystem/Directory.h"
#include "SharedLibrary.h"

using namespace darknessNight::CppUnitTestFramework;
using namespace darknessNight::DependencyContainer;
using namespace darknessNight::Filesystem;
using namespace darknessNight::SharedLibrary;

namespace darknessNight {
	namespace TestsRunner {
		class TestsDiscover {
			std::vector<TestSuitePtr> suites;
			const std::string dllFuncName = "getTestsFromDynamicTestsLibrary";
			std::shared_ptr<DynamicLibrary> dynamicLibrary = DIContainer::Get<DynamicLibrary>();
			std::shared_ptr<Directory> directory = DIContainer::Get<Directory>();
		public:
			void findAll(std::vector<std::string> paths, std::vector<std::string> extensions) {
				std::string pattern = prepareSearchPattern(extensions);
				searchLibraries(paths, pattern);
			}

		private:
			void searchLibraries(std::vector<std::string> &paths, std::string &pattern) {
				for (auto path : paths) {
					auto dir = directory->get(path);
					searchLibrariesInDir(dir, pattern);
				}
			}

			void searchLibrariesInDir(std::shared_ptr<Directory> &directory, std::string & pattern) {
				for (auto dir : directory->searchElements(pattern)) {
					getTestsIfLibraryIsCorrect(dir.getPath());
				}
			}

			void getTestsIfLibraryIsCorrect(std::string &path) {
				try {
					tryGetTests(path);
				}
				catch (SharedLibrary::LibraryLoadException) {}
				catch (SharedLibrary::FunctionLoadException) {
					dynamicLibrary->freeLibrary(path);
				}
			}

			void tryGetTests(std::string & path) {
				auto func = dynamicLibrary->importFunction<TestContainer*()>(path, dllFuncName);
				TestContainer* container = func();
				for (auto suite : container->getAllTestSuites())
					suites.push_back(suite);
			}

			std::string prepareSearchPattern(std::vector<std::string> &extensions) {
				std::string pattern = ".*/.*\\.(";
				addExtensionsToPattern(extensions, pattern);
				return pattern;
			}

			void addExtensionsToPattern(std::vector<std::string> & extensions, std::string &pattern) {
				for (auto ext : extensions)
					pattern += ext + "|";
				pattern = pattern.substr(0, pattern.size() - 1) + ")";
			}
		public:
			std::vector<std::string> getSuitesNames() {
				std::vector<std::string> names;
				for (auto suite : suites) {
					names.push_back(suite->getName());
				}
				return names;
			}

			std::vector<TestCasePtr> getTestsList() {
				std::vector<TestCasePtr> tests;
				for (auto suite : suites) {
					for(auto test: suite->getTestCaseList())
						tests.push_back(nullptr);
				}
				return tests;
			}
		};
	}
}
