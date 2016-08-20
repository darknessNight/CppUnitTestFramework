#include "stdafx.h"
#include "CppUnitTest.h"
#include <CppUnitTestsFramework\TestCase.h>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace CppUnitTestsFramework
{
	namespace UnitTests {
		void testFuncDoNothing() {
			int e = 2 + 2;
		}

		void testFuncCrashed() {
			throw exception();
		}

		TEST_CLASS(TestCaseTests)
		{
			private: TestCase getTestObject(TestCase::TestMethod method) {
				TestCase testCase(method);
				return testCase;
			}
			public:TEST_METHOD(RunTest_HasNothingDoFunc_CheckMethodReturnTrue) {
				TestCase testCase = getTestObject(testFuncDoNothing);
				bool testRunned = testCase.runTest();
				Assert::IsTrue(testRunned);
			}

			public:TEST_METHOD(RunTest_HasMockFunc_CheckFuncIsInvoked) {
				bool invoked = false;
				TestCase testCase = NewFunction(invoked);
				testCase.runTest();

				Assert::IsTrue(invoked);
			}

			private: TestCase NewFunction(bool& invoked)
			{
				TestCase::TestMethod mockFunc = [&]() {
					invoked = true;
				};
				return getTestObject(mockFunc);
			}

			public:TEST_METHOD(SetUp_HasDoNothingFunc_CheckFuncIsInvoked) {
				TestCase testCase = getTestObject(testFuncDoNothing);
				testCase.runTest();
				Assert::IsTrue(testCase.setUpRunned);
			}
		};
	}
}