#pragma once
#include "FunctionTester.h"
#include "TestReport.h"
#include <memory>

namespace darknessNight::CppUnitTestFramework::UnitTests {class TestCase {
	public:
		typedef std::unique_ptr<FunctionTester> FunctionTesterPtr;
	protected:
		FunctionTesterPtr test;
		TestReport report;
	protected:
		TestCase(){}
	public:
		TestCase(FunctionTesterPtr& tester, string name){
			test.swap(tester);
			report.testName = name;
		}

		void setFileAndLine(string file, unsigned int line) {
			report.testFile = file;
			report.testLine = line;
		}

		void setSuite(string suite) {
			report.testSuite = suite;
		}

		void setCategory(TestCategory cat) {
			report.testCategory = cat;
		}

		TestReport runTestAndGetReport() {
			TestResult result = runTest();
			return getReport(result);
		}

		TestReport getReport(TestResult result)
		{
			TestReport returnReport = report;
			returnReport.testResult = result;
			return returnReport;
		}

		virtual TestResult runTest() {
			TestResult result = test->runTest();
			return result;
		}
	};
}