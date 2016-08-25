#include "stdafx.h"
#include "TestHelperFuncAndClassess.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace darknessNight_CppUnitTestFramework::UnitTests {
	TEST_CLASS(FunctionTesterTests)
	{
		typedef std::unique_ptr<FunctionTester> FunctionTesterPointer;

	private:
		std::unique_ptr<MockFunctionTester> getTestObject(FunctionTester::TestMethod method) {
			std::unique_ptr<MockFunctionTester> functionTester = std::make_unique<MockFunctionTester>(method);
			return functionTester;
		}

	public:
		TEST_METHOD(RunTest_HasNullptr_CheckThrowsException) {
			auto testFunc = [&]() { getTestObject(nullptr); };
			Assert::ExpectException<NullPointerException>(testFunc);
		}

	public:
		TEST_METHOD(RunTest_HasNullptr_CheckExceptionHasNameFunc) {
			auto testFunc = [&]() { getTestObject(nullptr); };
			try {
				testFunc();
				Assert::Fail();
			}
			catch (NullPointerException ex) {
				StringAssert::Constains("Argument cannot be nullptr in", ex.what());
			}
		}

	public:
		TEST_METHOD(RunTest_HasNothingDoFunc_CheckMethodReturnSuccess) {
			FunctionTesterPointer functionTester = getTestObject(testDoNothingFunc);
			TestResult testRunned = functionTester->runTest();
			Assert::IsTrue(testRunned.isSuccess());
		}

	public:
		TEST_METHOD(RunTest_HasCollapseFunc_CheckMethodReturnFailure) {
			FunctionTesterPointer functionTester = getTestObject(testCollapseFunc);
			TestResult runResult = functionTester->runTest();
			Assert::IsTrue(runResult.isFailure());
		}

	public:
		TEST_METHOD(RunTest_HasCollapseFunc_CheckResultHasExceptionMessage) {
			FunctionTesterPointer functionTester = getTestObject(testCollapseFunc);
			TestResult runResult = functionTester->runTest();
			StringAssert::Constains(methodFailedString, runResult.getErrorMessage());
		}

	public:
		TEST_METHOD(RunTest_HasMockFunc_CheckFuncIsInvoked) {
			bool invoked = false;
			FunctionTesterPointer functionTester = getTestObjectWithMockTestFunc(invoked);

			functionTester->runTest();

			Assert::IsTrue(invoked);
		}

	private:
		FunctionTesterPointer getTestObjectWithMockTestFunc(bool& invoked)
		{
			FunctionTester::TestMethod mockFunc = [&]() {
				invoked = true;
			};
			return getTestObject(mockFunc);
		}

	public:
		TEST_METHOD(RunTest_HasThrowsAssertException_CheckIsReported) {
			FunctionTesterPointer functionTester = getTestObject(testThrowingAssertFunc);
			TestResult runResult = functionTester->runTest();
			StringAssert::Constains(methodFailedString, runResult.getFullMessage(), L"Not have message");
			StringAssert::Constains("Assert failed: ", runResult.getFullMessage(), L"Not assert type message");
		}

	public:
		TEST_METHOD(RunTest_HasThrowsAssertException_CheckIsCorrectReportedCause) {
			FunctionTesterPointer functionTester = getTestObject(testThrowingAssertFunc);
			TestResult runResult = functionTester->runTest();
			StringAssert::Constains("Assert failed", runResult.getCause());
		}

	public:
		TEST_METHOD(RunTest_HasThrowsCppException_CheckIsCorrectReportedCause) {
			FunctionTesterPointer functionTester = getTestObject(testCollapseFunc);
			TestResult runResult = functionTester->runTest();
			StringAssert::Constains("C++ exception", runResult.getCause());
		}

	public:
		TEST_METHOD(RunTest_HasNoThrowException_CheckIsCorrectReportedCause) {
			FunctionTesterPointer functionTester = getTestObject(testDoNothingFunc);
			TestResult runResult = functionTester->runTest();
			StringAssert::Constains("Success", runResult.getCause());
		}

	public:
		TEST_METHOD(SetUp_HasDoNothingFunc_CheckFuncIsInvoked) {
			std::unique_ptr<MockFunctionTester> functionTester = getTestObject(testDoNothingFunc);
			Assert::IsFalse(functionTester->setUpRunned);
			functionTester->runTest();
			Assert::IsTrue(functionTester->setUpRunned);
		}

	public:
		TEST_METHOD(TearDown_HasDoNothingFunc_CheckFuncIsInvoked) {
			std::unique_ptr<MockFunctionTester> functionTester = getTestObject(testDoNothingFunc);
			functionTester->runTest();
			Assert::IsTrue(functionTester->tearDownRunned);
		}

	public:
		TEST_METHOD(TearDown_HasCollapseFunc_CheckFuncIsInvoked) {
			std::unique_ptr<MockFunctionTester> functionTester = getTestObject(testCollapseFunc);
			functionTester->runTest();
			Assert::IsTrue(functionTester->tearDownRunned);
		}

	public:
		TEST_METHOD(SetUp_HasFunctionTesterCollapsed_CheckExceptionIsThrowed) {
			FunctionTesterPointer functionTester = getFakeFunctionTesterWithSetUpCollapse();
			TestResult runResult = functionTester->runTest();
			StringAssert::Constains("SetUp failed", runResult.getCause());
		}

	private:
		std::unique_ptr<FakeFunctionTester> getFakeFunctionTesterWithSetUpCollapse() {
			std::unique_ptr<FakeFunctionTester> fake = std::make_unique<FakeFunctionTester>();
			fake->collapseSetUp = true;
			return fake;
		}

	public:
		TEST_METHOD(TearDown_HasFunctionTesterCollapsed_CheckResultCauseTearDown) {
			FunctionTesterPointer functionTester = getFakeFunctionTesterWithTearDownCollapse();
			TestResult runResult= functionTester->runTest();
			StringAssert::Constains("TearDown failed", runResult.getCause());
		}


	public:
		TEST_METHOD(TearDown_HasFunctionTesterCollapsed_CheckResultHasExceptionMessage) {
			FunctionTesterPointer functionTester = getFakeFunctionTesterWithSetUpCollapse();
			TestResult runResult = functionTester->runTest();
			StringAssert::Constains(methodFailedString, runResult.getErrorMessage());
		}

	private:
		std::unique_ptr<FakeFunctionTester> getFakeFunctionTesterWithTearDownCollapse() {
			std::unique_ptr<FakeFunctionTester> fake = std::make_unique<FakeFunctionTester>();
			fake->collapseTearDown = true;
			return fake;
		}
	};
}
