#pragma once
#include "FunctionTester.h"
#include <memory>

namespace darknessNight::CppUnitTestFramework::UnitTests {
	class TestCategory {
	private:
		string name;
	public:
		TestCategory(){}

		TestCategory(string myName) {
			name = myName;
		}

		string getName() {
			return name;
		}
	};

	class TestRaport {
	private:
		TestResult testResult;
		string testName;
		string testFile;
		unsigned testLine;
		string testSuite;
		TestCategory testCategory;
		friend class TestCase;
	private:
		TestRaport():testResult(false){}
	public:
		TestResult getResult() {			
			return testResult;
		}

		string getTestName() {
			return "TestName";
		}

		string getFile() {
			return testFile;
		}

		unsigned getLine() {
			return testLine;
		}

		string getSuite() {
			return testSuite;
		}

		TestCategory getCategory() {
			return testCategory;
		}
	};

	class TestCase {
	public:
		typedef std::unique_ptr<FunctionTester> FunctionTesterPtr;
	protected:
		FunctionTesterPtr test;
		TestRaport raport;
	protected:
		TestCase(){}
	public:
		TestCase(FunctionTesterPtr& tester, string name){
			test.swap(tester);
			raport.testName = name;
		}

		void setFileAndLine(string file, unsigned int line) {
			raport.testFile = file;
			raport.testLine = line;
		}

		void setSuite(string suite) {
			raport.testSuite = suite;
		}

		void setCategory(TestCategory cat) {
			raport.testCategory = cat;
		}

		TestRaport runTestAndGetRaport() {
			TestResult result = runTest();
			return getReport(result);
		}

		TestRaport getReport(TestResult result)
		{
			TestRaport returnRaport = raport;
			returnRaport.testResult = result;
			return returnRaport;
		}

		virtual TestResult runTest() {
			TestResult result = test->runTest();
			return result;
		}
	};
}