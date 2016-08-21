#include "stdafx.h"
#include <memory>
#include "TestHelperFuncAndClassess.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace darknessNight::CppUnitTestFramework::UnitTests {
	TEST_CLASS(FunctionTesterTests)
	{
		typedef std::unique_ptr<FunctionTester> FunctionTesterPointer;

	private:
		std::unique_ptr<FakeFunctionTester> getTestObject(FunctionTester::TestMethod method) {
			std::unique_ptr<FakeFunctionTester> testCase = std::make_unique<FakeFunctionTester>(method);
			return testCase;
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
			FunctionTesterPointer testCase = getTestObject(testDoNothingFunc);
			TestResult testRunned = testCase->runTest();
			Assert::IsTrue(testRunned.isSuccess());
		}

	public:
		TEST_METHOD(RunTest_HasCollapseFunc_CheckMethodReturnFailure) {
			FunctionTesterPointer testCase = getTestObject(testCollapseFunc);
			TestResult runResult = testCase->runTest();
			Assert::IsTrue(runResult.isFailure());
		}

	public:
		TEST_METHOD(RunTest_HasCollapseFunc_CheckResultHasExceptionMessage) {
			FunctionTesterPointer testCase = getTestObject(testCollapseFunc);
			TestResult runResult = testCase->runTest();
			StringAssert::Constains(methodFailedString, runResult.getErrorMessage());
		}

	public:
		TEST_METHOD(RunTest_HasMockFunc_CheckFuncIsInvoked) {
			bool invoked = false;
			FunctionTesterPointer testCase = getTestObjectWithMockTestFunc(invoked);

			testCase->runTest();

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
		TEST_METHOD(RunTest_HasThrowsAssertException_CheckIsRaported) {
			FunctionTesterPointer testCase = getTestObject(testThrowingAssertFunc);
			TestResult runResult = testCase->runTest();
			StringAssert::Constains(methodFailedString, runResult.getFullMessage(), L"Not have message");
			StringAssert::Constains("Assert failed: ", runResult.getFullMessage(), L"Not assert type message");
		}

	public:
		TEST_METHOD(RunTest_HasThrowsAssertException_CheckIsCorrectRaportedCause) {
			FunctionTesterPointer testCase = getTestObject(testThrowingAssertFunc);
			TestResult runResult = testCase->runTest();
			StringAssert::Constains("Assert failed", runResult.getCause());
		}

	public:
		TEST_METHOD(RunTest_HasThrowsCppException_CheckIsCorrectRaportedCause) {
			FunctionTesterPointer testCase = getTestObject(testCollapseFunc);
			TestResult runResult = testCase->runTest();
			StringAssert::Constains("C++ exception", runResult.getCause());
		}

	public:
		TEST_METHOD(RunTest_HasNoThrowException_CheckIsCorrectRaportedCause) {
			FunctionTesterPointer testCase = getTestObject(testDoNothingFunc);
			TestResult runResult = testCase->runTest();
			StringAssert::Constains("Success", runResult.getCause());
		}

	public:
		TEST_METHOD(SetUp_HasDoNothingFunc_CheckFuncIsInvoked) {
			std::unique_ptr<FakeFunctionTester> testCase = getTestObject(testDoNothingFunc);
			Assert::IsFalse(testCase->setUpRunned);
			testCase->runTest();
			Assert::IsTrue(testCase->setUpRunned);
		}

	public:
		TEST_METHOD(TearDown_HasDoNothingFunc_CheckFuncIsInvoked) {
			std::unique_ptr<FakeFunctionTester> testCase = getTestObject(testDoNothingFunc);
			testCase->runTest();
			Assert::IsTrue(testCase->tearDownRunned);
		}

	public:
		TEST_METHOD(TearDown_HasCollapseFunc_CheckFuncIsInvoked) {
			std::unique_ptr<FakeFunctionTester> testCase = getTestObject(testCollapseFunc);
			testCase->runTest();
			Assert::IsTrue(testCase->tearDownRunned);
		}

	public:
		TEST_METHOD(SetUp_HasFunctionTesterCollapsed_CheckExceptionIsThrowed) {
			FunctionTesterPointer testCase = getFakeFunctionTesterWithSetUpCollapse();
			auto testFunc = [&]() {testCase->runTest(); };
			Assert::ExpectException<SetUpException>(testFunc);
		}

	private:
		std::unique_ptr<FakeCollapseFunctionTester> getFakeFunctionTesterWithSetUpCollapse() {
			std::unique_ptr<FakeCollapseFunctionTester> fake = std::make_unique<FakeCollapseFunctionTester>();
			fake->collapseSetUp = true;
			return fake;
		}


	public:
		TEST_METHOD(SetUp_HasFunctionTesterCollapsed_CheckExceptionHasInnerException) {
			FunctionTesterPointer testCase = getFakeFunctionTesterWithSetUpCollapse();
			try {
				testCase->runTest();
				Assert::Fail();
			}
			catch (SetUpException ex) {
				StringAssert::Constains(methodFailedString, ex.what());
			}
		}

	public:
		TEST_METHOD(TearDown_HasFunctionTesterCollapsed_CheckExceptionIsThrowed) {
			FunctionTesterPointer testCase = getFakeFunctionTesterWithTearDownCollapse();
			Assert::ExpectException<TearDownException>([&]() {testCase->runTest(); });
		}

	private:
		std::unique_ptr<FakeCollapseFunctionTester> getFakeFunctionTesterWithTearDownCollapse() {
			std::unique_ptr<FakeCollapseFunctionTester> fake = std::make_unique<FakeCollapseFunctionTester>();
			fake->collapseTearDown = true;
			return fake;
		}
	};
}
