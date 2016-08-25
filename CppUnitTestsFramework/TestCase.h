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
		void setName(string name);
		TestCase();
	public:
		string getName();
		void setFileAndLine(string file, unsigned int line);
		void setSuite(string suite);
		void setCategory(TestCategory cat);
		TestReport runTestAndGetReport();
		TestReport getReport(TestResult result);
		TestReport getReportWithoutResult();
		virtual TestResult runTest();
		void prepareFunctionTester();
	};
	typedef std::shared_ptr<TestCase> TestCasePtr;
}