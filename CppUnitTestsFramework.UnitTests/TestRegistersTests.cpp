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

	class FakeTestRegisterContainerAccess :public TestRegisterContainerAccess {
	public:
		using TestRegisterContainerAccess::getTestContainer;
		using TestRegisterContainerAccess::getTestSuite;
	};

	TEST_CLASS(TestClassRegistererTests)
	{
	public:

		TEST_METHOD_CLEANUP(tearDown) {
			TestsCollectionExport::clear();
		}

		TEST_METHOD_INITIALIZE(setUp) {
			tearDown();
		}

		TEST_METHOD(getTestContainer_CheckNoThrow)
		{
			FakeTestRegisterContainerAccess testRegister;
			try {
				testRegister.getTestContainer();
			}
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(getTestSuite_HasCorrectName_CheckNoThrow)
		{
			FakeTestRegisterContainerAccess testRegister;
			try {
				testRegister.getTestSuite("Unnamed");
			}
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(getTestSuite_HasCorrectName_CheckThrowingTestRegisterException)
		{
			FakeTestRegisterContainerAccess testRegister;
			auto testFunc = [&]() {testRegister.getTestSuite("NoExists testSuite"); };
			Assert::ExpectException<TestRegisterException>(testFunc);
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
									   "DoNothingMethod", typeid(TestClassForRegisterTests).name(), __FILE__, __LINE__);
		}

	public:
		TEST_METHOD(RegisterSetUpFunc_HasCorrectMethod_CheckHasTestCaseInSuite){
			actRegisterMethod();
			string name = TestClassForRegisterTests::myName;
			SetUpRegister setUpReg([]() {throw exception(); }, name);
			TestSuitePtr testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName(name);
			TestReport report=testSuite->runTestsAndGetReports()[0];
			StringAssert::Constains("SetUp failed", report.getResult().getCause());
		}

	public:
		TEST_METHOD(RegisterTearDownFunc_HasCorrectMethod_CheckHasTestCaseInSuite) {
			actRegisterMethod();
			string name = TestClassForRegisterTests::myName;
			TearDownRegister setUpReg([]() {throw exception(); }, name);
			TestSuitePtr testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName(name);
			TestReport report = testSuite->runTestsAndGetReports()[0];
			StringAssert::Constains("TearDown failed", report.getResult().getCause());
		}
	};
}