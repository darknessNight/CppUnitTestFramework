#pragma once
#include "TestCase.h"
#include <vector>
#include <map>

namespace darknessNight::CppUnitTestFramework {
	class TestSuite:public ConfigurableTest {
	protected:
		std::vector<TestCasePtr> testArray;
		std::map<std::string, TestCasePtr> testMap;
		TestCategory testCategory;
		std::string suiteName="";
	public:
		typedef std::vector<TestReport> TestReportArray;
		virtual std::string getName();
	public:
		void addTestCase(TestCasePtr testCase);
		void setCategory(TestCategory cat);
		const TestCategory& getCategory();
		TestReportArray runTestsAndGetReports();
		TestReport runTestAndGetReport(std::string name);
		std::vector<std::string> getTestCaseList();
		
	protected:
		TestCasePtr findTestFromName(string name);
		TestReport prepareAndRunTest(TestCasePtr test);
		virtual void prepareTestCase(TestCasePtr test);
		void setSuiteNameIfNotSetted();
	};
	typedef std::shared_ptr<TestSuite> TestSuitePtr;
}