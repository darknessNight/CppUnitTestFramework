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
			std::shared_ptr<DynamicLibrary> dynamicLibrary;
			std::shared_ptr<Directory> directory;
		public:
			TestExecutor(std::shared_ptr<Directory>, std::shared_ptr<DynamicLibrary>);
			void stop();
			void safeClear();
			TestReport runTest(TestCasePtr testCase);
			TestReport runTest(TestSuitePtr testSuite, std::string testName);
			std::vector<TestReport> runTests(std::vector<TestCasePtr> testCases);
			std::vector<TestReport> runTests(TestSuitePtr testSuite);
			std::vector<TestReport> runTests(std::string path, std::vector<std::string> names);
			std::vector<TestReport> runTestsFromFile(std::string path);
		protected:
			std::vector<TestCasePtr> getAllTestsInFile(std::string& path);
			std::vector<TestReport> filterAndRunTests(std::vector<TestCasePtr> tests, std::vector<std::string>& names);
			void runTestWithNameHasInFilter(std::vector<std::string>& names, TestCasePtr& test, std::vector<TestReport>& reports);
			void deleteNameFromNamesTab(std::vector<std::string>::iterator& name, std::vector<std::string>& names);
			bool isTestHasPassFullname(TestCasePtr& test, std::string& name);
			void runTestAndSaveReport(std::vector<TestReport>& reports, TestCasePtr& test);
		};
	}
}
