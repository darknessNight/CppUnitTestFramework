#pragma once
#include <CppUnitTestFramework/TestCase.h>
#include <CppUnitTestFramework/TestSuite.h>
#include <vector>
#include "TestsDiscover.h"

using namespace darknessNight::CppUnitTestFramework;

namespace darknessNight {
	namespace TestsRunner {
		class TestExecutor {
		private:
			bool running = false;
		public:
			void stop() {
				running = false;
			}

			TestReport runTest(TestCasePtr testCase) {
				return testCase->runTestAndGetReport();
			}

			TestReport runTest(TestSuitePtr testSuite, std::string testName) {
				return runTest(testSuite->getTestCase(testName));
			}

			std::vector<TestReport> runTests(std::vector<TestCasePtr> testCases) {
				running = true;
				std::vector<TestReport> reports;
				for (auto test : testCases) {
					if (!running)break;
					reports.push_back(runTest(test));
				}
				return reports;
			}

			std::vector<TestReport> runTests(TestSuitePtr testSuite) {
				return runTests(testSuite->getTestCases());
			}

			std::vector<TestReport> runTests(std::string path, std::vector<std::string> names) {
				auto tests=getAllTestsInFile(path);
				return filterAndRunTests(tests, names);
			}

			std::vector<TestCasePtr> getAllTestsInFile(std::string &path) {
				TestsDiscover discover;
				discover.findInFile(path);
				return discover.getTestsList();
			}

			std::vector<TestReport> filterAndRunTests(std::vector<TestCasePtr> tests, std::vector<std::string> &names) {
				running = true;
				std::vector<TestReport> reports;
				for (auto test : tests) {
					if (!running)break;
					runTestWithNameHasInFilter(names, test, reports);
				}
				return reports;
			}

			void runTestWithNameHasInFilter(std::vector<std::string> & names, TestCasePtr &test, std::vector<TestReport> & reports) {
				for (auto name = names.begin(); name != names.end(); name++)
					if (isTestHasPassFullname(test, *name)) {
						runTestAndSaveReport(reports, test);
						deleteNameFromNamesTab(name, names);
						break;
					}
			}

			void deleteNameFromNamesTab(std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::string>>> &name, std::vector<std::string> & names) {
				swap(*name, *names.rbegin());
				names.pop_back();
			}

			bool isTestHasPassFullname(TestCasePtr & test, std::string &name) {
				return test->getReportWithoutResult().getFullName() == name;
			}

			void runTestAndSaveReport(std::vector<TestReport> & reports, TestCasePtr & test) {
				reports.push_back(test->runTestAndGetReport());
			}
		};
	}
}
