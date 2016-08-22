#include "stdafx.h"
#include <CppUnitTestsFramework\TestSuite.h>
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
			std::vector<TestReport> testReports = testSuite.getReports();
			Assert::AreEqual(0U, testReports.size());
		}

	public:
		TEST_METHOD(RunTests_HasTwoTestCases_CheckReturnTwoElementArray)
		{
			TestSuite testSuite = getTestSuiteWithTwoFakeTestCase();
			std::vector<TestReport> testReports = testSuite.getReports();
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
			std::vector<TestReport> testReports = testSuite.getReports();
			StringAssert::Constains("Test", testReports[0].getTestName());
		}

	public:
		TEST_METHOD(RunTests_HasTwoTestCaseWithCollapsingSetUp_CheckReturnCorrectErrorCause)
		{
			TestSuite testSuite = getTestSuiteWithTwoTestCaseWithDoNothingFunc();
			testSuite.setSetUpMethod([]() {throw std::exception(); });

			std::vector<TestReport> testReports = testSuite.getReports();
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
			std::vector<TestReport> testReports = testSuite.getReports();
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