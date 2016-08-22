#pragma once
#include "FunctionTester.h"
#include "TestReport.h"
#include <memory>

namespace darknessNight::CppUnitTestFramework {
	class TestCase: public ConfigurableTest {
	public:
		typedef std::unique_ptr<FunctionTester> FunctionTesterPtr;
	protected:
		FunctionTesterPtr functionTester;
		TestReport report;
	protected:
		void setName(string name) {
			report.testName = name;
		}
	public:
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
			functionTester->setSetUpMethod(setUpMethod);
			functionTester->setTearDownMethod(tearDownMethod);
			TestResult result = functionTester->runTest();
			return result;
		}
	};
	typedef std::shared_ptr<TestCase> TestCasePtr;
}