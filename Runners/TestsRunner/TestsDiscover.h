#pragma once
#include <vector>
#include <string>
#include <CppUnitTestFramework/TestSuite.h>
#include <DependencyContainer/DependencyContainer.h>
#include "Filesystem/Directory.h"

using namespace darknessNight::CppUnitTestFramework;
using namespace darknessNight::DependencyContainer;
using namespace darknessNight::Filesystem;

namespace darknessNight {
	namespace TestsRunner {
		class TestsDiscover {
			std::vector<TestSuitePtr> suites;
		public:
			void findAll(std::vector<std::string> paths, std::vector<std::string> extensions) {
				std::string pattern = "";
				for (auto path : paths) {
					auto directory = DIContainer::Get<Directory>()->get(path);
					for (auto dir : directory->searchElements(pattern)) {
						std::string tmp = dir.getPath();
						suites.push_back(nullptr);
					}
				}
			}

			std::vector<TestSuitePtr> getSuites() {
				return suites;
			}
		};
	}
}
