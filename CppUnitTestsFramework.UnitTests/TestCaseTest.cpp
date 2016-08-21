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
		TestCasePointer getTestObject(TestCase::FunctionTesterPtr& fakeTester, string testName) {
			return std::unique_ptr<TestCase>(new TestCase(fakeTester, testName));
		}

	public:
		TEST_METHOD(GetRaportFromTest_HasFakeFunctionTester_CheckGetResultFromTestReturnCorrectData)
		{
			TestCasePointer testCase=getTestObjectWithFakeResult();
			TestRaport testRaport = testCase->runTestAndGetRaport();
			StringAssert::Constains("TestError", testRaport.getResult().getErrorMessage());
		}

	private:
		TestCasePointer getTestObjectWithFakeResult()
		{
			FakeFunctionTester* fakeTester = new FakeFunctionTester;
			fakeTester->returnResult = TestResult("TestError");			
			TestCasePointer testCase = getTestObject(TestCase::FunctionTesterPtr(fakeTester), "TestName");
			return testCase;
		}

	public:
		TEST_METHOD(GetRaportFromTest_HasFakeFunctionTester_CheckGetTestNameReturnCorrectData)
		{
			TestCasePointer testCase = getTestObjectWithFakeResult();
			TestRaport testRaport = testCase->runTestAndGetRaport();
			StringAssert::Constains("TestName", testRaport.getTestName());
		}

	public:
		TEST_METHOD(GetRaportFromTest_SettedFileAndLine_CheckGetFileAndLineIsCorrect)
		{
			TestCasePointer testCase = getTestObjectWithFakeResult();
			testCase->setFileAndLine("TestFile", 4);
			TestRaport testRaport = testCase->runTestAndGetRaport();
			StringAssert::Constains("TestFile", testRaport.getFile(), L"File");
			Assert::AreEqual(4U, testRaport.getLine(), L"Line");
		}

	public:
		TEST_METHOD(GetRaportFromTest_SettedSuite_CheckSuiteIsCorrect)
		{
			TestCasePointer testCase = getTestObjectWithFakeResult();
			testCase->setSuite("TestSuite");
			TestRaport testRaport = testCase->runTestAndGetRaport();
			StringAssert::Constains("TestSuite", testRaport.getSuite());
		}

	public:
		TEST_METHOD(GetRaportFromTest_SettedCategory_CheckGetCategoryIsCorrect)
		{
			TestCasePointer testCase = getTestObjectWithFakeResult();
			TestCategory category("TestCategory");
			testCase->setCategory(category);
			TestRaport testRaport = testCase->runTestAndGetRaport();
			StringAssert::Constains("TestCategory", testRaport.getCategory().getName());
		}
	};
}