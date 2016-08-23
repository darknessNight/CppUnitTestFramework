#include "stdafx.h"
#include <CppUnitTestsFramework\TestSuiteClass.h>
#include <CppUnitTestsFramework\TestContainer.h>
#include <CppUnitTestsFramework\TestCaseFunc.h>
#include "TestHelperFuncAndClassess.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight::CppUnitTestFramework::UnitTests {
	TEST_CLASS(TestContainerTests)
	{
	public:
		TEST_METHOD(getTestSuiteByName_HasTwoNamedTestSuites_CheckReturnCorrectPtr)
		{
			TestContainer container = getTestObjectWithTwoTestSuites();
			TestSuitePtr testSuite = container.getTestSuiteByName("TestSuite2");
			Assert::IsFalse(testSuite==nullptr);
			StringAssert::Constains("TestSuiteClass", testSuite->getName());
		}

	private:
		TestContainer getTestObjectWithTwoTestSuites() {
			TestContainer container;
			container.addTestSuite(new TestSuiteInstanceCreator<TestSuite>("TestSuite1"));
			container.addTestSuite(new TestSuiteInstanceCreator<TestSuiteClass>("TestSuite2"));
			return container;
		}
	public:
		TEST_METHOD(getTestSuiteByName_HasTwoNamedTestSuitesTryGetEmpty_CheckReturnNullptr)
		{
			TestContainer container = getTestObjectWithTwoTestSuites();
			TestSuitePtr testSuite = container.getTestSuiteByName("TestSuiteNoExists");
			Assert::IsTrue(testSuite == nullptr);
		}

		TEST_METHOD(registerTestCase_HasCorrectName_CheckIsAddedToHimSuite) {
			TestContainer container = prepareAndActAddTestToTestSuite();
			AssertAddTestCaseIsInCorrectSuite(container);
		}
	private:
		TestContainer prepareAndActAddTestToTestSuite() {
			TestContainer container = getTestObjectWithTwoTestSuites();
			TestCasePtr testCase = getFakeTestCase("TestCase1");
			container.registerTestCase("TestSuite2", testCase);
			return container;
		}

		TestCasePtr getFakeTestCase(string name) {
			TestCase::FunctionTesterPtr fakeTester(new FakeFunctionTester);
			TestCasePtr testCase(new TestCaseFuncTester(fakeTester, name));
			return testCase;
		}

		void AssertAddTestCaseIsInCorrectSuite(TestContainer &container) {
			TestSuitePtr testSuite2 = container.getTestSuiteByName("TestSuite2");
			std::vector<string>testCaseList2 = testSuite2->getTestCaseList();
			Assert::AreEqual(1U, testCaseList2.size());
		}
	public:
		TEST_METHOD(registerTestCase_HasCorrectName_CheckIsNotAddedToOtherSuites) {
			TestContainer container = prepareAndActAddTestToTestSuite();
			AssertAddTestCaseIsNotInInCorrectSuite(container);
		}

	private:
		void AssertAddTestCaseIsNotInInCorrectSuite(TestContainer& container) {
			TestSuitePtr testSuite1 = container.getTestSuiteByName("TestSuite1");
			std::vector<string>testCaseList1 = testSuite1->getTestCaseList();
			Assert::AreEqual(0U, testCaseList1.size());
		}

	public:
		TEST_METHOD(registerTestCase_HasTestCaseWithNoSuiteName_CheckAddToUnnamed) {
			TestContainer container;
			TestCasePtr testCase = getFakeTestCase("TestCase");
			container.registerTestCase("", testCase);
			AssertRegisterdTestCaseToUnnamedSuite(container);
		}

	private:
		void AssertRegisterdTestCaseToUnnamedSuite(darknessNight::CppUnitTestFramework::TestContainer &container)
		{
			std::vector<string> listOfTestCase = container.getTestSuiteByName("Unnamed")->getTestCaseList();
			Assert::AreEqual(1U, listOfTestCase.size());
			StringAssert::Constains("TestCase", listOfTestCase[0]);
		}

	public:
		TEST_METHOD(registerTestCase_HasTestCaseWithNoExistsSuiteName_CheckThrowException) {
			TestContainer container;
			TestCasePtr testCase = getFakeTestCase("TestCase");
			auto testFunc = [&]() {container.registerTestCase("", testCase); };
			Assert::ExpectException<NotFoundException>(testFunc);
		}
	};
}