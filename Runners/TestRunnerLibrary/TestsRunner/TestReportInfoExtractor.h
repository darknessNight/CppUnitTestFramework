#pragma once
#include "TestReportCategoryContainer.h"

namespace darknessNight {
	namespace TestsRunner {
		class TestReportInfoExtract {
		public:
			static std::string getResult(TestReport &test);
			static std::string getDurationGroupIndex(TestReport& report, std::initializer_list<int>& groupsList);
		private:
			static bool findDurationGroup(int group, long long time, std::initializer_list<int>& groupsList);
			static std::string getGroupIndexString(bool overGroup, int group);
		};
	}
}