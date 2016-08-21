#pragma once
#include "TestCase.h"
#include <vector>

namespace darknessNight::CppUnitTestFramework {
	class TestSuite {
		std::vector<TestCasePtr> testArray;
	public:
		void addTestCase(TestCasePtr testCase) {
			testArray.push_back(testCase);
		}

		std::vector<TestReport> getReports() {
			std::vector<TestReport> returnTab;
			for each(TestCasePtr test in testArray)
				returnTab.push_back(test->runTestAndGetReport());
			return returnTab;
		}
	};
}