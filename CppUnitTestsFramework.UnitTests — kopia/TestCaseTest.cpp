#include "stdafx.h"
#include <CppUnitTestsFramework\TestCase.h>
#include <memory>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace darknessNight::CppUnitTestFramework::UnitTests {
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

	const string methodFailedString = "MethodFailed";
	static void testDoNothingFunc() {
	}

	static void testCollapseFunc() {
		throw exception(methodFailedString.c_str());
	}

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
			StringAssert::Constains(methodFailedString, runResult.getMessage());
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
	};
}
