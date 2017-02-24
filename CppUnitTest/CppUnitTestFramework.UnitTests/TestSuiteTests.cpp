#include "stdafx.h"
#include <CppUnitTestFramework\TestSuite.h>
#include <CppUnitTestFramework\TestCaseFunc.h>
#include <CppUnitTestFramework\TestCaseIgnored.h>
#include "TestHelperFuncAndClassess.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {
	namespace CppUnitTestFramework {
		namespace UnitTests {
			class TestSuiteTest :public TestSuite {
			public:
				TestSuiteTest() :TestSuite() {}
				TestSuiteTest(std::string name) :TestSuite(name) {}
			};

			TEST_CLASS(TestSuiteTests) {
			public:
				TEST_METHOD(RunTests_HasNoTests_CheckReturnEmptyArray) {
					TestSuite testSuite;
					TestSuite::TestReportArray testReports = testSuite.runTestsAndGetReports();
					Assert::AreEqual(0U, (unsigned)testReports.size());
				}

			public:
				TEST_METHOD(RunTests_HasTwoTestCases_CheckReturnTwoElementArray) {
					TestSuite testSuite = getTestSuiteWithTwoFakeTestCase();
					TestSuite::TestReportArray testReports = testSuite.runTestsAndGetReports();
					Assert::AreEqual(2U, (unsigned)testReports.size());
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
				TEST_METHOD(RunTests_HasOneTestCase_CheckReturnCorrectRaport) {
					TestSuite testSuite = getTestSuiteWithTwoFakeTestCase();
					TestSuite::TestReportArray testReports = testSuite.runTestsAndGetReports();
					StringAssert::Constains("Test", testReports[0].getTestName());
				}

			public:
				TEST_METHOD(RunTests_HasTwoTestCaseWithCollapsingSetUp_CheckReturnCorrectErrorCause) {
					TestSuite testSuite = getTestSuiteWithTwoTestCaseWithDoNothingFunc();
					testSuite.setSetUpMethod([]() {throw exception(); });

					TestSuite::TestReportArray testReports = testSuite.runTestsAndGetReports();
					for each(TestReport report in testReports)
						StringAssert::Constains("SetUp failed", report.getResult().getCause());
				}

			private:
				TestSuite getTestSuiteWithTwoTestCaseWithDoNothingFunc() {
					TestSuite testSuite;
					addDoNothingTestToTestSuite(testSuite, 0);
					addDoNothingTestToTestSuite(testSuite, 1);
					return testSuite;
				}

				void addDoNothingTestToTestSuite(TestSuite &testSuite, int number) {
					TestCase::FunctionTesterPtr tester(new FunctionTester(testDoNothingFunc));
					TestCasePtr testCase(new TestCaseFuncTester(tester, "Test" + std::to_string(number)));
					testSuite.addTestCase(testCase);
				}

			public:
				TEST_METHOD(RunTestOneTest_HasTwoTestCase_CheckReturnResult) {
					TestSuite testSuite = getTestSuiteWithTwoTestCaseWithDoNothingFunc();

					TestReport report = testSuite.runTestAndGetReport("Test1");
					Assert::IsTrue(report.getResult().isSuccess());
				}

			public:
				TEST_METHOD(RunTests_HasTwoTest_CheckReturnCorrectSuiteName) {
					TestSuite testSuite = getTestSuiteWithTwoTestCaseWithDoNothingFunc();
					TestSuite::TestReportArray testReports = testSuite.runTestsAndGetReports();
					StringAssert::Constains("TestSuite", testReports[0].getSuiteName());
				}

			public:
				TEST_METHOD(getTestCaseArrayLists_HasTwoTest_CheckReturnAllNames) {
					TestSuite testSuite = getTestSuiteWithTwoTestCaseWithDoNothingFunc();
					std::vector<std::string> keys = testSuite.getTestCaseList();
					Assert::AreEqual(2U, (unsigned)keys.size());
					for each(auto key in keys)
						StringAssert::Constains("Test", key);
				}

			public:
				TEST_METHOD(getName_HasChildClass_CheckReturnChildClassName) {
					TestSuiteTest test;
					std::string name = test.getName();
					StringAssert::Constains("TestSuiteTest", test.getName());
				}

				TEST_METHOD(getTestCases_HasSampleTest_CheckReturnConfiguredTest) {
					TestSuiteTest testSuite("TestSuiteTest");
					testSuite.addTestCase(TestCasePtr(new TestCaseIgnored("Name", "Res")));
					TestCasePtr testCase = testSuite.getTestCases()[0];
					Assert::AreEqual<std::string>("TestSuiteTest", testCase->getReportWithoutResult().getSuiteName());
				}
			};
		}
	}
}