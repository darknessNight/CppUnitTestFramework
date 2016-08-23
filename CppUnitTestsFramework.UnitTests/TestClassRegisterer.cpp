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
			TestSuitePtr resultSuite = TestExportCollection::getTestContainer().getTestSuiteByName("MySuite");
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
			std::vector<string> resultList = getRegisterFuncsList();
			Assert::AreEqual(1U, resultList.size());
			StringAssert::Constains("DoNothingFunc", resultList[0]);
		}

		std::vector<string> getRegisterFuncsList() {
			TestSuitePtr resultSuite = TestExportCollection::getTestContainer().getTestSuiteByName("MySuite");
			std::vector<string> resultList = resultSuite->getTestCaseList();
			return resultList;
		}

		void actRegisterFunc()
		{
			TestClassRegister<TestSuite> addSuite("class MySuite");
			TestFuncRegister addFunc([]() {}, "DoNothingFunc", "MySuite");
		}

	public:
		TEST_METHOD(RegisterMethod_HasCorrectFunc_CheckHasTestCaseInSuite)
		{
			actRegisterFunc();
			assertRegisterFunc();
		}
	};
}