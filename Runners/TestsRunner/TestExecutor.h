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

			void setTestDurationTime(darknessNight::CppUnitTestFramework::TestReport &report, std::chrono::time_point<std::chrono::steady_clock> &start) {
				auto end = std::chrono::high_resolution_clock::now();
				report.getResult().setTime((end - start));
			}

			std::vector<TestReport> runTests(std::vector<TestCasePtr> testCases) {
				std::vector<TestReport> reports;
				for (auto test : testCases)
					reports.push_back(runTest(test));
				return reports;
			}

			std::vector<TestReport> runTests(TestSuitePtr testSuite) {
				std::vector<TestReport> reports;
				for (auto test : testSuite->getTestCases())
					reports.push_back(runTest(test));
				return reports;
			}
		};
	}
}