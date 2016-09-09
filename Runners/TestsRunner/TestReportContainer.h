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
				return report1.getResult().getDurationTime() < report2.getResult().getDurationTime();
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

			std::map<std::string, std::vector<TestReport>> getReportsGroupByDuration(std::initializer_list<int> groupsList) {
				std::map<std::string, std::vector<TestReport>> ret;
				for (auto report : reportsArray) {
					auto groupIndex = getDurationGroupIndex(report, groupsList);
					ret[groupIndex].push_back(report);
				}
				return ret;
			}

			std::string getDurationGroupIndex(TestReport& report,std::initializer_list<int> &groupsList) {
				int group;
				auto time = std::chrono::duration_cast<std::chrono::milliseconds>(report.getResult().getDurationTime()).count();
				auto overGroup=findDurationGroup(group, time, groupsList);
				return getGroupIndexString(overGroup,group);
			}

			bool findDurationGroup(int &group, long long &time, std::initializer_list<int> &groupsList) {
				for (auto it = groupsList.begin(); it != groupsList.end(); it++) {
					group = *it;
					if (time < group) {
						return true;
					}
				}
				return false;
			}

			std::string getGroupIndexString(bool overGroup, int& group) {
				if (overGroup)
					return "<" + std::to_string(group);
				else
					return ">=" + std::to_string(group);
			}
		};
	}
}