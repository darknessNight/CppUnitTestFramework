#include "stdafx.h"
#include <CppUnitTestsFramework\TestSuite.h>
#include <CppUnitTestsFramework\TestCaseFunc.h>
#include "TestHelperFuncAndClassess.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight::CppUnitTestFramework::UnitTests {
	class TestSuiteTest:public TestSuite{
	};

	TEST_CLASS(TestSuiteTests)
	{
	public:
		TEST_METHOD(RunTests_HasNoTests_CheckReturnEmptyArray)
		{
			TestSuite testSuite;
			TestSuite::TestReportArray testReports = testSuite.runTestsAndGetReports();
			Assert::AreEqual(0U, testReports.size());
		}

	public:
		TEST_METHOD(RunTests_HasTwoTestCases_CheckReturnTwoElementArray)
		{
			TestSuite testSuite = getTestSuiteWithTwoFakeTestCase();
			TestSuite::TestReportArray testReports = testSuite.runTestsAndGetReports();
			Assert::AreEqual(2U, testReports.size());
		}

	private:
		TestSuite getTestSuiteWithTwoFakeTestCase() {
			TestSuite testSuite;
			addFakeTestToTestSuite(testSuite);
			addFakeTestToTestSuite(testSuite);
			return testSuite;
		}

		void addFakeTestToTestSuite(TestSuite &testSuite) {
			TestCase::FunctionTesterPtr fakeTester(new FakeFunctionTester);
			TestCasePtr testCase(new TestCaseFuncTester(fakeTester, "Test"));
			testSuite.addTestCase(testCase);
		}

	public:
		TEST_METHOD(RunTests_HasOneTestCase_CheckReturnCorrectRaport)
		{
			TestSuite testSuite = getTestSuiteWithTwoFakeTestCase();
			TestSuite::TestReportArray testReports = testSuite.runTestsAndGetReports();
			StringAssert::Constains("Test", testReports[0].getTestName());
		}

	public:
		TEST_METHOD(RunTests_HasTwoTestCaseWithCollapsingSetUp_CheckReturnCorrectErrorCause)
		{
			TestSuite testSuite = getTestSuiteWithTwoTestCaseWithDoNothingFunc();
			testSuite.setSetUpMethod([]() {throw std::exception(); });

			TestSuite::TestReportArray testReports = testSuite.runTestsAndGetReports();
			for each(TestReport report in testReports)
				StringAssert::Constains("SetUp failed", report.getResult().getCause());
		}

	private:
		TestSuite getTestSuiteWithTwoTestCaseWithDoNothingFunc() {
			TestSuite testSuite;
			addDoNothingTestToTestSuite(testSuite);
			addDoNothingTestToTestSuite(testSuite);
			return testSuite;
		}

		void addDoNothingTestToTestSuite(TestSuite &testSuite) {
			TestCase::FunctionTesterPtr tester(new FunctionTester(testDoNothingFunc));
			TestCasePtr testCase(new TestCaseFuncTester(tester, "Test"));
			testSuite.addTestCase(testCase);
		}

	public:
		TEST_METHOD(RunTests_HasTwoTest_CheckReturnCorrectSuiteName)
		{
			TestSuite testSuite = getTestSuiteWithTwoTestCaseWithDoNothingFunc();
			TestSuite::TestReportArray testReports = testSuite.runTestsAndGetReports();
			StringAssert::Constains("TestSuite", testReports[0].getSuiteName());
		}
	public:
		TEST_METHOD(getName_HasChildClass_CheckReturnChildClassName) {
			TestSuiteTest test;
			std::string name= test.getName();
			StringAssert::Constains("TestSuiteTest", test.getName());
		}
	};
}