#pragma once
#include "TestCase.h"
#include <vector>

namespace darknessNight::CppUnitTestFramework {
	class TestSuite:public ConfigurableTest {
		std::vector<TestCasePtr> testArray;
		TestCategory testCategory;
		std::string myName;
	public:

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

		std::vector<TestReport> getReports() {
			std::vector<TestReport> returnTab;
			for each(TestCasePtr test in testArray) {
				prepareTestCase(test);
				returnTab.push_back(test->runTestAndGetReport());
			}
			return returnTab;
		}

	protected:
		virtual void prepareTestCase(TestCasePtr test) {
			test->setSetUpMethod(setUpMethod);
			test->setTearDownMethod(tearDownMethod);
			test->setCategory(testCategory);
			test->setSuite(getName());
		}

		void setSuiteNameIfNotSetted()
		{
			if (myName.size() <= 0) {
				std::string myName = typeid(*this).name();
				myName = myName.substr(strlen("class "));
			}
		}
	};
}