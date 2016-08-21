#include "stdafx.h"
#include <CppUnitTestsFramework\TestCaseMethod.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight::CppUnitTestFramework::UnitTests {		
	class TestMethodClass:public ConfigurableTest {
	public:
		void doNothingMethod() {
		}
	};

	TEST_CLASS(TestCaseMethodTests)
	{
	private:
		TestCaseMethod getTestObject(ConfigurableTest::TestMethod method) {
			return TestCaseMethod(method);
		}

	public:
		TEST_METHOD(RunTest_HasDoNothingFuncButNotHaveObject_CheckThrowException)
		{
			TestCaseMethod testCase = getTestObject(static_cast<ConfigurableTest::TestMethod>(&TestMethodClass::doNothingMethod));
			auto func = [&]() { testCase.runTest(); };
			Assert::ExpectException<std::exception>(func);
		}

	public:
		TEST_METHOD(RunTest_HasDoNothingFuncAndObject_CheckReturnRunResult)
		{
			ConfigurableTestPtr obj = ConfigurableTestPtr(new TestMethodClass);
			TestCaseMethod testCase = getTestObject(static_cast<ConfigurableTest::TestMethod>(&TestMethodClass::doNothingMethod));
			testCase.setTestObj(obj);
			TestResult result=testCase.runTest();
			Assert::IsTrue(result.isSuccess());
		}
	};
}