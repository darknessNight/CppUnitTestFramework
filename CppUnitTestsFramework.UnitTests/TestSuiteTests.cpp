#include "stdafx.h"
#include <CppUnitTestsFramework\TestSuite.h>
#include "TestHelperFuncAndClassess.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight::CppUnitTestFramework::UnitTests {		
	TEST_CLASS(TestSuiteTests)
	{
	public:
		TEST_METHOD(RunTests_HasNoTests_CheckReturnEmptyArray)
		{
			TestSuite testSuite;
			std::vector<TestReport> testReports = testSuite.getReports();
			Assert::AreEqual(0U, testReports.size());
		}

	public:
		TEST_METHOD(RunTests_HasTwoTestCases_CheckReturnTwoElementArray)
		{
			TestSuite testSuite;
			TestCasePtr tester=TestCasePtr(new TestCaseFuncTester(TestCase::FunctionTesterPtr(new FakeFunctionTester),"Test"));
			testSuite.addTestCase(tester);
			tester = TestCasePtr(new TestCaseFuncTester(TestCase::FunctionTesterPtr(new FakeFunctionTester), "Test"));
			testSuite.addTestCase(tester);

			std::vector<TestReport> testReports = testSuite.getReports();
			Assert::AreEqual(2U, testReports.size());
		}

	public:
		TEST_METHOD(RunTests_HasOneTestCase_CheckReturnCorrectReport)
		{
			TestSuite testSuite;
			TestCasePtr tester = TestCasePtr(new TestCaseFuncTester(TestCase::FunctionTesterPtr(new FakeFunctionTester), "Test"));
			testSuite.addTestCase(tester);

			std::vector<TestReport> testReports = testSuite.getReports();
			StringAssert::Constains("Test", testReports[0].getTestName());
		}
	};
}