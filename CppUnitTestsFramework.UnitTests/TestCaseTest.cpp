#include "stdafx.h"
#include "TestHelperFuncAndClassess.h"
#include <CppUnitTestsFramework\TestCase.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight::CppUnitTestFramework::UnitTests {
	TEST_CLASS(TestCaseTest)
	{
	private:
		typedef std::unique_ptr<TestCase> TestCasePointer;

	private:
		TestCasePointer getTestObject(TestCaseFuncTester::FunctionTesterPtr& fakeTester, string testName) {
			return std::unique_ptr<TestCase>(new TestCaseFuncTester(fakeTester, testName));
		}

	public:
		TEST_METHOD(GetReportFromTest_HasFakeFunctionTester_CheckGetResultFromTestReturnCorrectData)
		{
			TestCasePointer testCase=getTestObjectWithFakeResult();
			TestReport testReport = testCase->runTestAndGetReport();
			StringAssert::Constains("TestError", testReport.getResult().getErrorMessage());
		}

	private:
		TestCasePointer getTestObjectWithFakeResult()
		{
			FakeFunctionTester* fakeTester = new FakeFunctionTester;
			fakeTester->returnResult = TestResult("TestError");			
			TestCasePointer testCase = getTestObject(TestCaseFuncTester::FunctionTesterPtr(fakeTester), "TestName");
			return testCase;
		}

	public:
		TEST_METHOD(GetReportFromTest_HasFakeFunctionTester_CheckGetTestNameReturnCorrectData)
		{
			TestCasePointer testCase = getTestObjectWithFakeResult();
			TestReport testReport = testCase->runTestAndGetReport();
			StringAssert::Constains("TestName", testReport.getTestName());
		}

	public:
		TEST_METHOD(GetReportFromTest_SettedFileAndLine_CheckGetFileAndLineIsCorrect)
		{
			TestCasePointer testCase = getTestObjectWithFakeResult();
			testCase->setFileAndLine("TestFile", 4);
			TestReport testReport = testCase->runTestAndGetReport();
			StringAssert::Constains("TestFile", testReport.getFile(), L"File");
			Assert::AreEqual(4U, testReport.getLine(), L"Line");
		}

	public:
		TEST_METHOD(GetReportFromTest_SettedSuite_CheckSuiteIsCorrect)
		{
			TestCasePointer testCase = getTestObjectWithFakeResult();
			testCase->setSuite("TestSuite");
			TestReport testReport = testCase->runTestAndGetReport();
			StringAssert::Constains("TestSuite", testReport.getSuite());
		}

	public:
		TEST_METHOD(GetReportFromTest_SettedCategory_CheckGetCategoryIsCorrect)
		{
			TestCasePointer testCase = getTestObjectWithFakeResult();
			TestCategory category("TestCategory");
			testCase->setCategory(category);
			TestReport testReport = testCase->runTestAndGetReport();
			StringAssert::Constains("TestCategory", testReport.getCategory().getName());
		}
	};
}