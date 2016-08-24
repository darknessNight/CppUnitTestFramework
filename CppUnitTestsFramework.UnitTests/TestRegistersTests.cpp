#include "stdafx.h"
#include <CppUnitTestsFramework\TestRegisterer.h>
#include <CppUnitTestsFramework\TestSuiteClass.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight::CppUnitTestFramework::UnitTests {
	class TestClassForRegisterTests :public TestSuiteClass {
	public:
		static string myName;
		void DoNothingMethod() {}
	};
	string TestClassForRegisterTests::myName = string(typeid(TestClassForRegisterTests).name()).substr(strlen("class "));

	TEST_CLASS(TestClassRegistererTests)
	{
	public:

		TEST_METHOD_CLEANUP(tearDown) {
			TestsCollectionExport::clear();
		}

		TEST_METHOD(RegisterClass_HasCorrectClassAndName_CheckHasSuite)
		{
			actRegisterClass();
			assertRegisterClass("MySuite");
		}

	private:
		void assertRegisterClass(string name)
		{
			try {
				TestSuitePtr resultSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName(name);
			}
			catch (NotFoundException ex) {
				Assert::Fail();
			}			
		}

		void actRegisterClass()
		{
			TestClassRegister<TestSuite> addSuite("MySuite");
		}

		TEST_METHOD(RegisterClass_HasCorrectClassAndNoHaveName_CheckHasSuiteAndAutoDetectName)
		{
			TestClassRegister<TestClassForRegisterTests> addSuite;
			assertRegisterClass(TestClassForRegisterTests::myName);
		}

	public:
		TEST_METHOD(RegisterFunc_HasCorrectFunc_CheckHasTestCaseInSuite)
		{
			actRegisterFunc();
			assertRegisterFunc("MySuite", "DoNothingFunc");
		}

	private:
		void actRegisterFunc()
		{
			TestClassRegister<TestSuite> addTest("MySuite");
			TestFuncRegister addFunc([]() {}, "DoNothingFunc", "MySuite", __FILE__, __LINE__);
		}

		void assertRegisterFunc(string suite, string func)
		{
			TestSuitePtr testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName(suite);
			AssertHasFuncInSuite(testSuite, func);
			AssertHasCorrectFile(testSuite, func);
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

	public:
		TEST_METHOD(RegisterMethod_HasCorrectMethod_CheckHasTestCaseInSuite)
		{
			actRegisterMethod();
			assertRegisterFunc(TestClassForRegisterTests::myName, "DoNothingMethod");
		}

		void actRegisterMethod() {
			TestClassRegister<TestClassForRegisterTests> addTest;
			TestMethodRegister addFunc((ConfigurableTest::TestMethod)&TestClassForRegisterTests::DoNothingMethod,
									   "DoNothingMethod", TestClassForRegisterTests::myName, __FILE__, __LINE__);
		}

	public:
		TEST_METHOD(VisualStudioVersion_RegisterMethod_HasCorrectMethod_CheckHasTestCaseInSuite)
		{
			actRegisterMethod_VS();
			assertRegisterFunc(TestClassForRegisterTests::myName, "DoNothingMethod");
		}

		void actRegisterMethod_VS() {
			TestClassRegister<TestClassForRegisterTests> addTest;
			TestMethodRegister_VS<(ConfigurableTest::TestMethod)&TestClassForRegisterTests::DoNothingMethod>
			addFunc("DoNothingMethod", TestClassForRegisterTests::myName, __FILE__, __LINE__);
		}
	};
}