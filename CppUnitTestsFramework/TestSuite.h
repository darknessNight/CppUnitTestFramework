#pragma once
#include "TestCase.h"
#include <vector>
#include <map>

namespace darknessNight::CppUnitTestFramework {
	class TestSuite:public ConfigurableTest {
		std::vector<TestCasePtr> testArray;
		std::map<std::string, TestCasePtr> testMap;
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
			testMap[testCase->getName()]= testCase;
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

		TestReport runTestAndGetReport(std::string name) {
			TestCasePtr test=findTestFromName(name);
			return prepareAndRunTest(test);
		}

		std::vector<std::string> getTestCaseList() {
			std::vector<string> array;
			for each(auto el in testMap)
				array.push_back(el.first);
			return array;
		}

	protected:
		TestCasePtr findTestFromName(string name) {
			TestCasePtr test = testMap[name];
			if(test==nullptr)
				throw NotFoundException("Not found TestCase in TestSuite");
			return test;
		}

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
	typedef std::shared_ptr<TestSuite> TestSuitePtr;
}