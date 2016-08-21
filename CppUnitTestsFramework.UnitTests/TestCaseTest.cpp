#include "stdafx.h"
#include <CppUnitTestsFramework\TestCase.h>
#include <CppUnitTestsFramework\AssertExceptions.h>
#include <memory>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace darknessNight::CppUnitTestFramework::UnitTests {
	const string methodFailedString = "MethodFailed";
	static void testDoNothingFunc() {
	}

	static void testCollapseFunc() {
		throw exception(methodFailedString.c_str());
	}

	static void testThrowingAssertFunc() {
		throw AssertException(methodFailedString);
	}

	class FakeTestCase : public TestCase {
	public:
		bool setUpRunned = false;
		bool tearDownRunned = false;
	public:
		FakeTestCase(TestCase::TestMethod method) :TestCase(method) {
		}

		void setUp() override {
			setUpRunned = true;
			tearDownRunned = false;
		}

		void tearDown() override {
			tearDownRunned = true;
		}
	};

	class SpecialException :public std::exception {
	public:
		SpecialException(string message) :exception(message.c_str()){}
	};

	class FakeCollapseTestCase : public TestCase {
	public:
		bool collapseSetUp = false;
		bool collapseTearDown = false;
	public:
		FakeCollapseTestCase() :TestCase(testDoNothingFunc) {
		}

		void setUp() override {
			if (collapseSetUp)
				throw SpecialException(methodFailedString);
		}

		void tearDown() override {
			if (collapseTearDown)
				throw SpecialException(methodFailedString);
		}
	};

	TEST_CLASS(TestCaseTests)
	{
		typedef std::unique_ptr<TestCase> TestCasePointer;

	private:
		std::unique_ptr<FakeTestCase> getTestObject(TestCase::TestMethod method) {
			std::unique_ptr<FakeTestCase> testCase = std::make_unique<FakeTestCase>(method);
			return testCase;
		}
	public:
		TEST_METHOD(RunTest_HasNothingDoFunc_CheckMethodReturnSuccess) {
			TestCasePointer testCase = getTestObject(testDoNothingFunc);
			TestResult testRunned = testCase->runTest();
			Assert::IsTrue(testRunned.isSuccess());
		}

	public:
		TEST_METHOD(RunTest_HasCollapseFunc_CheckMethodReturnFailure) {
			TestCasePointer testCase = getTestObject(testCollapseFunc);
			TestResult runResult = testCase->runTest();
			Assert::IsTrue(runResult.isFailure());
		}

	public:
		TEST_METHOD(RunTest_HasCollapseFunc_CheckResultHasExceptionMessage) {
			TestCasePointer testCase = getTestObject(testCollapseFunc);
			TestResult runResult = testCase->runTest();
			StringAssert::Constains(methodFailedString, runResult.getErrorMessage());
		}

	public:
		TEST_METHOD(RunTest_HasMockFunc_CheckFuncIsInvoked) {
			bool invoked = false;
			TestCasePointer testCase = getTestObjectWithMockTestFunc(invoked);

			testCase->runTest();

			Assert::IsTrue(invoked);
		}

	private:
		TestCasePointer getTestObjectWithMockTestFunc(bool& invoked)
		{
			TestCase::TestMethod mockFunc = [&]() {
				invoked = true;
			};
			return getTestObject(mockFunc);
		}

	public:
		TEST_METHOD(RunTest_HasThrowsAssertException_CheckIsRaported) {
			TestCasePointer testCase = getTestObject(testThrowingAssertFunc);
			TestResult runResult = testCase->runTest();
			StringAssert::Constains(methodFailedString, runResult.getFullMessage(), L"Not have message");
			StringAssert::Constains("Assert failed: ", runResult.getFullMessage(), L"Not assert type message");
		}

	public:
		TEST_METHOD(RunTest_HasThrowsAssertException_CheckIsCorrectRaportedCause) {
			TestCasePointer testCase = getTestObject(testThrowingAssertFunc);
			TestResult runResult = testCase->runTest();
			StringAssert::Constains("Assert failed", runResult.getCause());
		}

	public:
		TEST_METHOD(RunTest_HasThrowsCppException_CheckIsCorrectRaportedCause) {
			TestCasePointer testCase = getTestObject(testCollapseFunc);
			TestResult runResult = testCase->runTest();
			StringAssert::Constains("C++ exception", runResult.getCause());
		}

	public:
		TEST_METHOD(RunTest_HasNoThrowException_CheckIsCorrectRaportedCause) {
			TestCasePointer testCase = getTestObject(testDoNothingFunc);
			TestResult runResult = testCase->runTest();
			StringAssert::Constains("Success", runResult.getCause());
		}

	public:
		TEST_METHOD(SetUp_HasDoNothingFunc_CheckFuncIsInvoked) {
			std::unique_ptr<FakeTestCase> testCase = getTestObject(testDoNothingFunc);
			Assert::IsFalse(testCase->setUpRunned);
			testCase->runTest();
			Assert::IsTrue(testCase->setUpRunned);
		}

	public:
		TEST_METHOD(TearDown_HasDoNothingFunc_CheckFuncIsInvoked) {
			std::unique_ptr<FakeTestCase> testCase = getTestObject(testDoNothingFunc);
			testCase->runTest();
			Assert::IsTrue(testCase->tearDownRunned);
		}

	public:
		TEST_METHOD(TearDown_HasCollapseFunc_CheckFuncIsInvoked) {
			std::unique_ptr<FakeTestCase> testCase = getTestObject(testCollapseFunc);
			testCase->runTest();
			Assert::IsTrue(testCase->tearDownRunned);
		}

	public:
		TEST_METHOD(SetUp_HasTestCaseCollapsed_CheckExceptionIsThrowed) {
			TestCasePointer testCase = getFakeTestCaseWithSetUpCollapse();
			Assert::ExpectException<SetUpException>([&]() {testCase->runTest(); });
		}

	private:
		std::unique_ptr<FakeCollapseTestCase> getFakeTestCaseWithSetUpCollapse() {
			std::unique_ptr<FakeCollapseTestCase> fake = std::make_unique<FakeCollapseTestCase>();
			fake->collapseSetUp = true;
			return fake;
		}


	public:
		TEST_METHOD(SetUp_HasTestCaseCollapsed_CheckExceptionHasInnerException) {
			TestCasePointer testCase = getFakeTestCaseWithSetUpCollapse();
			try {
				testCase->runTest();
			}
			catch (SetUpException ex) {
				StringAssert::Constains(methodFailedString, ex.what());
			}
		}

	public:
		TEST_METHOD(TearDown_HasTestCaseCollapsed_CheckExceptionIsThrowed) {
			TestCasePointer testCase = getFakeTestCaseWithTearDownCollapse();
			Assert::ExpectException<TearDownException>([&]() {testCase->runTest(); });
		}

	private:
		std::unique_ptr<FakeCollapseTestCase> getFakeTestCaseWithTearDownCollapse() {
			std::unique_ptr<FakeCollapseTestCase> fake = std::make_unique<FakeCollapseTestCase>();
			fake->collapseTearDown = true;
			return fake;
		}
	};
}
