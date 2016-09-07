#pragma once
#include <algorithm>
#include "TestReportCategoryContainer.h"

using namespace darknessNight::CppUnitTestFramework;

namespace darknessNight {
	namespace TestsRunner {
		class TestReportContainer {
			std::vector<TestReport> reportsArray;
		public:
			void addReports(std::initializer_list<TestReport> reports) {
				for (auto report : reports)
					reportsArray.push_back(report);
			}

			std::vector<TestReport> getReportsSortByName() {
				std::sort(reportsArray.begin(), reportsArray.end(), &TestReportContainer::sortByName);
				return reportsArray;
			}

			static bool sortByName(TestReport& report1, TestReport& report2) {
				return report1.getFullName() < report2.getFullName();
			}

			std::vector<TestReport> getReportsSortByTime() {
				std::sort(reportsArray.begin(), reportsArray.end(), &TestReportContainer::sortByTime);
				return reportsArray;
			}

			static bool sortByTime(TestReport& report1, TestReport& report2) {
				return report1.getResult().getTime() < report2.getResult().getTime();
			}

			CategoryContainer getReportsGroupByCategory() {
				CategoryContainer ret;
				for (auto test : reportsArray)
					ret.addReportToCat(test);
				return ret;
			}

			std::map<std::string,std::vector<TestReport>> getReportsGroupBySuite() {
				std::map<std::string, std::vector<TestReport>> ret;
				for (auto test : reportsArray) {
					addTestToField(test, ret);
				}

				return ret;
			}
			void addTestToField(darknessNight::CppUnitTestFramework::TestReport &test, std::map<std::string, std::vector<darknessNight::CppUnitTestFramework::TestReport>> &ret) {
				if (test.getResult().isSuccess())
					ret["Success"].push_back(test);
				else if (test.getResult().getCause() == "Ignored")
					ret["Ignored"].push_back(test);
				else ret["Failed"].push_back(test);
			}
		};
	}
}