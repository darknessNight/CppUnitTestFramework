#pragma once
#include <algorithm>
#include <functional>
#include "TestReportInfoExtractor.h"

using namespace darknessNight::CppUnitTestFramework;

namespace darknessNight {
	namespace TestsRunner {

		class TestReportContainer {
			std::vector<TestReport> reportsArray;
		public:
			void addReports(std::initializer_list<TestReport> reports);
			std::vector<TestReport> getReportsSortByName();
			std::vector<TestReport> getReportsSortByTime();
			CategoryContainer getReportsGroupByCategory();
			std::map<std::string, std::vector<TestReport>> getReportsGroupByResult();
			std::map<std::string, std::vector<TestReport>> getReportsGroupByDuration(std::initializer_list<int> groupsList);
			std::map<std::string, std::vector<TestReport>> getReportsGroupBySuite();
		private:
			template<typename T, typename U> std::map<T, std::vector<U>> groupBy(std::vector<U>& array, std::function<T(U&)> func);
			static bool sortByName(TestReport& report1, TestReport& report2);
			static bool sortByTime(TestReport& report1, TestReport& report2);
		};

		template<typename T, typename U>
		inline std::map<T, std::vector<U>> TestReportContainer::groupBy(std::vector<U>& array, std::function<T(U&)> func) {
			std::map<T, std::vector<U>> ret;
			for (auto el : array) {
				ret[func(el)].push_back(el);
			}
			return ret;
		}
	}
}