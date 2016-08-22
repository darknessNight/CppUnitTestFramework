#pragma once
#include "TestCase.h"
#include <vector>

namespace darknessNight::CppUnitTestFramework {
	class TestSuite:public ConfigurableTest {
		std::vector<TestCasePtr> testArray;
		TestCategory testCategory;
		std::string myName;
	public:
		typedef std::vector<TestReport> TestReportArray;

		virtual std::string getName() {
			setSuiteNameIfNotSetted();
			return myName;
		}

	public:
		void addTestCase(TestCasePtr testCase) {
			testArray.push_back(testCase);
		}

		void setCategory(TestCategory cat) {
			testCategory = cat;
		}

		TestReportArray runTestsAndGetReports() {
			TestReportArray returnTab;
			for each(TestCasePtr test in testArray) {
				TestReport report = prepareAndRunTest(test);
				returnTab.push_back(report);
			}
			return returnTab;
		}

	protected:
		TestReport prepareAndRunTest(TestCasePtr test) {
			prepareTestCase(test);
			return test->runTestAndGetReport();
		}

		virtual void prepareTestCase(TestCasePtr test) {
			test->setSetUpMethod(setUpMethod);
			test->setTearDownMethod(tearDownMethod);
			test->setCategory(testCategory);
			test->setSuite(getName());
		}

		void setSuiteNameIfNotSetted()
		{
			if (myName.size() <= 0) {
				myName = typeid(*this).name();
				myName = myName.substr(strlen("class "));
			}
		}
	};
}