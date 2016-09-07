#include "stdafx.h"
#include <CppUnitTestFramework/TestCaseIgnored.h>
#include <CppUnitTestFramework/TestSuite.h>
#include "../TestsRunner/TestExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace darknessNight::CppUnitTestFramework;

namespace darknessNight {
	namespace TestsRunner {
		namespace UnitTests {
			TEST_CLASS(TestExecutorTests) {
public:
	TEST_METHOD(RunTest_HasTest_CheckRunTest) {
		TestExecutor testExecutor;
		TestCasePtr testCase = TestCasePtr(new TestCaseIgnored("Test", "IgnoreResult"));
		TestResult result = testExecutor.runTest(testCase).getResult();
		Assert::AreEqual<std::string>("Ignored", result.getCause());
	}


	TEST_METHOD(RunTests_HasTwoTests_CheckRunAllTests) {
		std::vector<TestReport> reports = actRunTestsFromTestCasesList();
		AssertRunAllTests(reports);
	}

	std::vector<darknessNight::CppUnitTestFramework::TestReport> actRunTestsFromTestCasesList() {
		TestExecutor testExecutor;
		TestCasePtr testCase = TestCasePtr(new TestCaseIgnored("Test", "IgnoreResult"));
		return testExecutor.runTests({ testCase, testCase });
	}

	void AssertRunAllTests(std::vector<darknessNight::CppUnitTestFramework::TestReport> &raports) {
		Assert::AreEqual<unsigned>(2, raports.size());
		for (auto rap : raports)
			Assert::AreEqual<std::string>("Ignored", rap.getResult().getCause());
	}


	TEST_METHOD(RunTests_HasTestSuite_CheckRunAllTests) {
		auto reports=actRunTestsTestSuite();
		AssertRunAllTests(reports);
	}
	std::vector<darknessNight::CppUnitTestFramework::TestReport> actRunTestsTestSuite() {
		TestExecutor testExecutor;
		TestSuite testSuite=prepareTestSuite();
		return testExecutor.runTests(TestSuitePtr(&testSuite, [](void*) {}));
	}

	darknessNight::CppUnitTestFramework::TestSuite prepareTestSuite() {
		TestSuite testSuite("Suite");
		addToTestSuiteTestCases(testSuite);
		return testSuite;
	}

	void addToTestSuiteTestCases(darknessNight::CppUnitTestFramework::TestSuite &testSuite) {
		TestCasePtr testCase1 = TestCasePtr(new TestCaseIgnored("Test", "IgnoreResult"));
		TestCasePtr testCase2 = TestCasePtr(new TestCaseIgnored("Test2", "IgnoreResult"));
		for (auto test : { testCase1, testCase2 })
			testSuite.addTestCase(test);
	}

	TEST_METHOD(RunTests_HasTestSuite_CheckHasDurationTime) {
		auto reports = actRunTestsTestSuite();
		Assert::IsTrue(reports[0].getResult().getTime().count()>0);
	}

	TEST_METHOD(RunTest_HasTestSuiteAndTestCaseName_CheckReturnReport) {
		TestSuite testSuite=prepareTestSuite();
		TestExecutor executor;
		auto report=executor.runTest(TestSuitePtr(&testSuite, [](void*) {}), "Test");
		Assert::AreEqual<std::string>("Test", report.getTestName());
	}
			};
		}
	}
}