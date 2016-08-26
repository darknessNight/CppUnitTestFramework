#include "stdafx.h"
#include <CppUnitTestsFramework\TestRegisters.h>
#include <CppUnitTestsFramework\TestSuite.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight_CppUnitTestFramework::UnitTests {
	class TestClassForRegisterTests :public TestSuite {
	public:
		static std::string myName;
		static std::string myTypeName;
		void DoNothingMethod() {}
	};
	std::string TestClassForRegisterTests::myName = getClassName<TestClassForRegisterTests>();
	std::string TestClassForRegisterTests::myTypeName = typeid(TestClassForRegisterTests).name();

	class FakeTestRegisterContainerAccess :public TestRegisterContainerAccess {
	public:
		using TestRegisterContainerAccess::getTestContainer;
		using TestRegisterContainerAccess::getTestSuite;
	};

	TEST_CLASS(TestClassRegistererTests)
	{
		TestClassForRegisterTests* testClass;
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

		void assertRegisterClass(std::string name)
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

		TEST_METHOD(RegisterFunc_HasCorrectFunc_CheckHasTestCaseInSuite)
		{
			actRegisterFunc();
			assertRegisterFunc("MySuite", "DoNothingFunc");
		}

		void actRegisterFunc()
		{
			TestClassRegister<TestSuite> addTest("MySuite");
			TestFuncRegister addFunc([]() {}, "DoNothingFunc", "MySuite", __FILE__, __LINE__);
		}

		void assertRegisterFunc(std::string suite, std::string func)
		{
			try {
				tryAssertRegisterFunc(suite, func);
			}
			catch (exception ex) {
				Assert::Fail();
			}
		}

		void tryAssertRegisterFunc(std::string &suite, std::string &func)
		{
			TestSuitePtr testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName(suite);
			AssertHasFuncInSuite(testSuite, func);
			AssertHasCorrectFile(testSuite, func);
		}

		void AssertHasCorrectFile(darknessNight_CppUnitTestFramework::TestSuitePtr &testSuite, std::string name)
		{
			TestReport resultSuite = testSuite->runTestAndGetReport(name);
			Assert::IsTrue(resultSuite.getFile() == __FILE__);
		}

		void AssertHasFuncInSuite(darknessNight_CppUnitTestFramework::TestSuitePtr &testSuite, std::string name)
		{
			std::vector<std::string> resultList = getRegisterFuncsList(testSuite);
			Assert::AreEqual(1U, resultList.size());
			StringAssert::Constains(name, resultList[0]);
		}

		std::vector<std::string> getRegisterFuncsList(TestSuitePtr testSuite) {
			std::vector<std::string> resultList = testSuite->getTestCaseList();
			return resultList;
		}

		TEST_METHOD(RegisterMethod_HasCorrectMethodByLambda_CheckHasTestCaseInSuite)
		{
			TestClassForRegisterTests instance;
			actRegisterMethodByLambda(&instance);
			assertRegisterFunc(TestClassForRegisterTests::myName, "DoNothingMethod");
		}

		void actRegisterMethodByLambda(TestClassForRegisterTests* instance) {
			TestClassRegister<TestClassForRegisterTests> addTest;
			TestMethodRegister addFunc([=]() {instance->DoNothingMethod(); },
									   "DoNothingMethod", TestClassForRegisterTests::myTypeName, __FILE__, __LINE__);
		}

		TEST_METHOD(RegisterSetUpFunc_HasCorrectMethod_CheckHasTestCaseInSuite) {
			actRegisterSetUpMethod();
			assertHasRegisteredConfMethod("SetUp failed");
		}

		void actRegisterSetUpMethod()
		{
			TestClassForRegisterTests instance;
			actRegisterMethodByLambda(&instance);
			SetUpRegister setUpReg([]() {throw exception(); }, TestClassForRegisterTests::myName);
		}

		TEST_METHOD(RegisterTearDownFunc_HasCorrectMethod_CheckHasTestCaseInSuite) {
			actRegisterTearDownMethod();
			assertHasRegisteredConfMethod("TearDown failed");
		}

		void actRegisterTearDownMethod()
		{
			TestClassForRegisterTests instance;
			actRegisterMethodByLambda(&instance);
			TearDownRegister setUpReg([]() {throw exception(); }, TestClassForRegisterTests::myName);
		}

		void assertHasRegisteredConfMethod(std::string causeString)
		{
			TestSuitePtr testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName(TestClassForRegisterTests::myName);
			TestReport report = testSuite->runTestsAndGetReports()[0];
			StringAssert::Constains(causeString, report.getResult().getCause());
		}
		
		TEST_METHOD(RegisterClassWithCategory_CheckRemberCategory) {
			TestClassWithCategoryRegister<TestClassForRegisterTests> reg("TestName", TestCategory("FullCategory.NameCat.LastCat"));
			TestSuitePtr testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName("TestName");
			bool result=testSuite->getCategory()==TestCategory("FullCategory.NameCat.LastCat");
			Assert::IsTrue(result);
		}

	};
}