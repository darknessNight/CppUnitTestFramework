#include "stdafx.h"
#include "TestHelperFuncAndClassess.h"
#include <CppUnitTestFramework\TestCase.h>
#include <CppUnitTestFramework\TestCaseFunc.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {
	namespace CppUnitTestFramework {
		namespace UnitTests {
			TEST_CLASS(TestCaseTest) {
private:
	TestCasePtr getTestObject(TestCaseFuncTester::FunctionTesterPtr& fakeTester, std::string testName) {
		return std::unique_ptr<TestCase>(new TestCaseFuncTester(fakeTester, testName));
	}

public:
	TEST_METHOD(GetReportFromTest_HasFakeFunctionTester_CheckGetResultFromTestReturnCorrectData) {
		TestCasePtr testCase = getTestObjectWithPredefinedTestResult();
		TestReport testReport = testCase->runTestAndGetReport();
		StringAssert::Constains("TestError", testReport.getResult().getErrorMessage());
	}

private:
	TestCasePtr getTestObjectWithPredefinedTestResult() {
		TestCaseFuncTester::FunctionTesterPtr tester = getFakeTesterWithPredefinedResult();
		TestCasePtr testCase = getTestObject(tester, "TestName");
		return testCase;
	}
private:
	TestCaseFuncTester::FunctionTesterPtr getFakeTesterWithPredefinedResult() {
		FakeFunctionTester* fakeTester = new FakeFunctionTester;
		fakeTester->returnFakeResult = true;
		fakeTester->returnResult = TestResult("TestError");
		TestCaseFuncTester::FunctionTesterPtr tester(fakeTester);
		return tester;
	}

public:
	TEST_METHOD(GetReportFromTest_HasFakeFunctionTester_CheckGetTestNameReturnCorrectData) {
		TestCasePtr testCase = getTestObjectWithPredefinedTestResult();
		TestReport testReport = testCase->runTestAndGetReport();
		StringAssert::Constains("TestName", testReport.getTestName());
	}

public:
	TEST_METHOD(GetReportFromTest_SettedFileAndLine_CheckGetFileAndLineIsCorrect) {
		TestCasePtr testCase = getTestObjectWithPredefinedTestResult();
		testCase->setFileAndLine("TestFile", 4);
		TestReport testReport = testCase->runTestAndGetReport();
		StringAssert::Constains("TestFile", testReport.getFile(), L"File");
		Assert::AreEqual(4U, testReport.getLine(), L"Line");
	}

public:
	TEST_METHOD(GetReportFromTest_SettedSuite_CheckSuiteIsCorrect) {
		TestCasePtr testCase = getTestObjectWithPredefinedTestResult();
		testCase->setSuite("TestSuite");
		TestReport testReport = testCase->runTestAndGetReport();
		StringAssert::Constains("TestSuite", testReport.getSuiteName());
	}

public:
	TEST_METHOD(GetReportFromTest_SettedCategory_CheckGetCategoryIsCorrect) {
		TestCasePtr testCase = getTestObjectWithPredefinedTestResult();
		TestCategory category("TestCategory");
		testCase->setCategory(category);
		TestReport testReport = testCase->runTestAndGetReport();
		StringAssert::Constains("TestCategory", testReport.getCategory().getName());
	}

public:
	TEST_METHOD(SetSetUpMethod_SetThrowError_CheckReturnRaportWithSetUpFailedCause) {
		TestCasePtr testCase = getTestObjectWithDoNothingTest();
		testCase->setSetUpMethod([]() {throw exception(); });
		TestReport testReport = testCase->runTestAndGetReport();
		StringAssert::Constains("SetUp failed", testReport.getResult().getCause());
	}

public:
	TEST_METHOD(SetTearDownMethod_SetThrowError_CheckReturnRaportWithTearDownFailedCause) {
		TestCasePtr testCase = getTestObjectWithDoNothingTest();
		testCase->setTearDownMethod([]() {throw exception(); });
		TestReport testReport = testCase->runTestAndGetReport();
		StringAssert::Constains("TearDown failed", testReport.getResult().getCause());
	}

private:
	TestCasePtr getTestObjectWithDoNothingTest() {
		TestCaseFuncTester::FunctionTesterPtr tester(new FunctionTester(testDoNothingFunc));
		TestCasePtr testCase = getTestObject(tester, "TestName");
		return testCase;
	}
			};
		}
	}
}