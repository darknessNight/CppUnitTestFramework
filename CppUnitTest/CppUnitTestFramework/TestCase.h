#pragma once
#include <memory>
#include "FunctionTester.h"
#include "TestReport.h"

namespace darknessNight {
	namespace CppUnitTestFramework {
		class TestCase : public ConfigurableTest {
		public:
			typedef std::unique_ptr<FunctionTester> FunctionTesterPtr;
		protected:
			FunctionTesterPtr functionTester;
			TestReport report;
		public:
			std::string getName() const;
			void setFileAndLine(std::string file, unsigned int line);
			void setSuite(std::string suite);
			void setCategory(TestCategory cat);
			TestReport runTestAndGetReport();
			TestReport getReport(TestResult result) const;
			TestReport getReportWithoutResult() const;
			virtual TestResult runTest();
		protected:
			TestCase();
			void setName(std::string name);
			void prepareFunctionTester();
		};
		typedef std::shared_ptr<TestCase> TestCasePtr;
	}
}