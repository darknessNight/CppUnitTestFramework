#pragma once
#include <CppUnitTestFramework/TestCase.h>
#include <CppUnitTestFramework/TestSuite.h>
#include <vector>

using namespace darknessNight::CppUnitTestFramework;

namespace darknessNight {
	namespace TestsRunner {
		class TestExecutor {
		public:
			TestReport runTest(TestCasePtr testCase) {
				auto start = std::chrono::high_resolution_clock::now();
				auto report = testCase->runTestAndGetReport();
				setTestDurationTime(report, start);
				return report;
			}

			void setTestDurationTime(darknessNight::CppUnitTestFramework::TestReport &report, std::chrono::high_resolution_clock::time_point start) {
				auto end = std::chrono::high_resolution_clock::now();
				report.getResult().setDurationTime(std::chrono::duration_cast<TestResult::TimeDuration>(end - start));
			}

			TestReport runTest(TestSuitePtr testSuite, std::string testName) {
				return runTest(testSuite->getTestCase(testName));
			}

			std::vector<TestReport> runTests(std::vector<TestCasePtr> testCases) {
				std::vector<TestReport> reports;
				for (auto test : testCases)
					reports.push_back(runTest(test));
				return reports;
			}

			std::vector<TestReport> runTests(TestSuitePtr testSuite) {
				return runTests(testSuite->getTestCases());
			}
		};
	}
}
