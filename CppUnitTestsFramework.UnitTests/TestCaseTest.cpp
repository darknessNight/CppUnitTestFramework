#include "stdafx.h"
#include "CppUnitTest.h"
#include <CppUnitTestsFramework\TestCase.h>
#include <memory>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace CppUnitTestsFramework
{
	namespace UnitTests {
		void testDoNothingFunc() {
		}

		void testCollapseFunc() {
			throw exception();
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

			void tearDown() override{
				tearDownRunned = true;
			}
		};

		TEST_CLASS(TestCaseTests)
		{
		private:
			std::unique_ptr<FakeTestCase> getTestObject(TestCase::TestMethod method) {
				std::unique_ptr<FakeTestCase> testCase = std::make_unique<FakeTestCase>(method);
				return testCase;
			}
		public:
			TEST_METHOD(RunTest_HasNothingDoFunc_CheckMethodReturnSuccess) {
				std::unique_ptr<TestCase> testCase = getTestObject(testDoNothingFunc);
				bool testRunned = testCase->runTest();
				Assert::IsTrue(testRunned);
			}

		public:
			TEST_METHOD(RunTest_HasCollapseFunc_CheckMethodReturnFailure) {
				std::unique_ptr<FakeTestCase> testCase = getTestObject(testCollapseFunc);

				bool runResult=testCase->runTest();

				Assert::IsFalse(runResult);
			}

		public:
			TEST_METHOD(RunTest_HasCollapseFunc_CheckMethodReturnFailure) {
				std::unique_ptr<FakeTestCase> testCase = getTestObject(testCollapseFunc);

				bool runResult = testCase->runTest();

				Assert::IsFalse(runResult);
			}

		public:
			TEST_METHOD(RunTest_HasMockFunc_CheckFuncIsInvoked) {
				bool invoked = false;
				std::unique_ptr<TestCase> testCase = getTestObjectWithMockTestFunc(invoked);

				testCase->runTest();

				Assert::IsTrue(invoked);
			}

		private:
			std::unique_ptr<TestCase> getTestObjectWithMockTestFunc(bool& invoked)
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
}