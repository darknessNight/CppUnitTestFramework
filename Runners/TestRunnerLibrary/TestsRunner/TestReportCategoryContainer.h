#pragma once
#include <CppUnitTestFramework/TestReport.h>
#include <vector>
#include <map>

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

			std::map<std::string, CategoryContainer> getSubCats() {
				return subcats;
			}

			std::vector<TestReport>  getTestsReports() {
				return reports;
			}
		};
	}
}