#include "stdafx.h"
#include <CppUnitTestsFramework\TestRegisterer.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight::CppUnitTestFramework::UnitTests {
	TEST_CLASS(TestClassRegistererTests)
	{
	public:

		TEST_METHOD(RegisterClass_HasCorrectClass_CheckHasSuite)
		{
			actRegisterClass();
			assertRegisterClass();
		}

	private:
		void assertRegisterClass()
		{
			TestSuitePtr resultSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName("MySuite");
			bool notConstainsSuite = resultSuite == nullptr;
			Assert::IsFalse(notConstainsSuite);
		}

		void actRegisterClass()
		{
			TestClassRegister<TestSuite> addSuite("class MySuite");
		}

	public:
		TEST_METHOD(RegisterFunc_HasCorrectFunc_CheckHasTestCaseInSuite)
		{
			actRegisterFunc();
			assertRegisterFunc();
		}

	private:
		void assertRegisterFunc()
		{
			TestSuitePtr testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName("MySuite");
			AssertHasFuncInSuite(testSuite, "DoNothingFunc");
			AssertHasCorrectFile(testSuite, "DoNothingFunc");
		}

		void AssertHasCorrectFile(darknessNight::CppUnitTestFramework::TestSuitePtr &testSuite, string name)
		{
			TestReport resultSuite = testSuite->runTestAndGetReport(name);
			Assert::IsTrue(resultSuite.getFile() == __FILE__);
		}

		void AssertHasFuncInSuite(darknessNight::CppUnitTestFramework::TestSuitePtr &testSuite, string name)
		{
			std::vector<string> resultList = getRegisterFuncsList(testSuite);
			Assert::AreEqual(1U, resultList.size());
			StringAssert::Constains(name, resultList[0]);
		}

		std::vector<string> getRegisterFuncsList(TestSuitePtr testSuite) {
			std::vector<string> resultList = testSuite->getTestCaseList();
			return resultList;
		}

		void actRegisterFunc()
		{
			TestClassRegister<TestSuite> addTest("class MySuite");
			TestFuncRegister addFunc([]() {}, "DoNothingFunc", "MySuite", __FILE__, __LINE__);
		}

	public:/*
		TEST_METHOD(RegisterMethod_HasCorrectFunc_CheckHasTestCaseInSuite)
		{
			
			throw exception();
		}*/
	};
}