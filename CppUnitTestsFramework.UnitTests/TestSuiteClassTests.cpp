#include "stdafx.h"
#include <CppUnitTestsFramework\TestSuiteClass.h>
#include <CppUnitTestsFramework\TestCaseFunc.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight::CppUnitTestFramework::UnitTests {

	bool testMockSuccess = false;
	void testMethod() {
		testMockSuccess = true;
	}

	class TestClassBaseOnSuite :public TestSuiteClass {
	public:
		bool testSuccess = false;

		void testMethod() {
			testSuccess = true;
		}
		using TestSuiteClass::isMethodTestCase;
	};

	class TestCaseMethodChild :public TestCaseMethod {
	public:
		TestCaseMethodChild(ConfigurableTest::TestMethod method) :TestCaseMethod(method, ""){}
	};

	TEST_CLASS(TestSuiteClassTests)
	{
	private:
		ConfigurableTest::TestMethod getTestMethod() {
			return (ConfigurableTest::TestMethod)&TestClassBaseOnSuite::testMethod;
		}

	public:
		TEST_METHOD(isMethodTestCase_HasTestCaseMethod_CheckReturnTrue)
		{
			TestClassBaseOnSuite testSuite;
			TestCasePtr testCase(new TestCaseMethod(getTestMethod()));
			bool detectResult = testSuite.isMethodTestCase(testCase);
			Assert::IsTrue(detectResult);
		}

	public:
		TEST_METHOD(isMethodTestCase_HasTestCaseFunc_CheckReturnFalse)
		{
			TestClassBaseOnSuite testSuite;
			TestCasePtr testCase(new TestCaseFunc([]() {}, "name"));
			bool detectResult = testSuite.isMethodTestCase(testCase);
			Assert::IsFalse(detectResult);
		}

	public:
		TEST_METHOD(isMethodTestCase_HasTestCaseMethodChild_CheckReturnTrue)
		{
			TestClassBaseOnSuite testSuite;
			TestCasePtr testCase(new TestCaseMethodChild(getTestMethod()));
			bool detectResult = testSuite.isMethodTestCase(testCase);
			Assert::IsTrue(detectResult);
		}

	public:
		TEST_METHOD(injectObjectToTestCase_HasTestCaseMethodd_CheckSetMock)
		{
			TestClassBaseOnSuite testSuite;
			TestCasePtr testCase(new TestCaseMethod(getTestMethod()));
			testSuite.addTestCase(testCase);
			testSuite.runTestsAndGetReports();
			Assert::IsTrue(testSuite.testSuccess);
		}

	public:
		TEST_METHOD(injectObjectToTestCase_HasTestCaseFunc_CheckSetMock)
		{
			TestClassBaseOnSuite testSuite;
			TestCasePtr testCase(new TestCaseFunc(testMethod,""));
			testSuite.addTestCase(testCase);
			testSuite.runTestsAndGetReports();
			Assert::IsTrue(testMockSuccess);
		}
	};
}