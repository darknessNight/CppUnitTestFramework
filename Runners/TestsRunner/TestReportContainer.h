#pragma once
#include <CppUnitTestFramework/TestReport.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace darknessNight::CppUnitTestFramework;

namespace darknessNight {
	namespace TestsRunner {
		class CategoryContainer {
		private:
			std::map<std::string, CategoryContainer> subcats;
			std::vector<TestReport> reports;
		private:
			void addReportToSubCat(TestCategory index, TestReport& rep) {
				auto subCat = index.getSubCategory();
				if (subCat.getName().size() > 0)
					subcats[index.getName()].addReportToSubCat(index.getSubCategory(), rep);
				else subcats[index.getName()].reports.push_back(rep);
			}
		public:
			void addReportToCat(TestReport rep) {
				addReportToSubCat(rep.getCategory(), rep);
			}

			CategoryContainer& operator[](std::string index) {
				return subcats[index];
			}

			TestReport& operator[](int index) {
				return reports[index];
			}
		};

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
				for (auto test : reportsArray)
					ret[test.getSuiteName()].push_back(test);
				return ret;
			}
		};
	}
}