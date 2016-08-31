#pragma once
#include <vector>
#include <map>
#include "TestCase.h"

namespace darknessNight {
	namespace CppUnitTestFramework {
		class TestSuite :public ConfigurableTest {
		protected:
			std::vector<TestCasePtr> testArray;
			std::map<std::string, TestCasePtr> testMap;
			TestCategory testCategory;
			std::string suiteName = "";
		public:
			typedef std::vector<TestReport> TestReportArray;
			virtual std::string getName();
		public:
			void addTestCase(TestCasePtr testCase);
			void setCategory(TestCategory cat);
			const TestCategory& getCategory();
			TestReportArray runTestsAndGetReports();
			TestReport runTestAndGetReport(std::string name);
			const std::shared_ptr<const TestCase> getTestCase(std::string name);
			std::vector<std::string> getTestCaseList();

		protected:
			TestCasePtr findTestFromName(std::string name);
			TestReport prepareAndRunTest(TestCasePtr test);
			virtual void prepareTestCase(TestCasePtr test);
			void setSuiteNameIfNotSetted();
		};
		typedef std::shared_ptr<TestSuite> TestSuitePtr;
	}
}