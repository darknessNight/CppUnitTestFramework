#include "stdafx.h"
#include <CppUnitTestFramework/TestCaseIgnored.h>
#include <CppUnitTestFramework/TestSuite.h>
#include "../TestsRunner/TestExecutor.h"
#include "FakeDynamicLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace darknessNight::CppUnitTestFramework;

namespace darknessNight {
	namespace TestsRunner {
		namespace UnitTest {
			TEST_CLASS(TestExecutorTests) {
				std::shared_ptr<FakeDir> fakeDir;
				std::shared_ptr<FakeDynamicLibrary> fakeDynamicLibrary;

				TEST_METHOD_INITIALIZE(SetUp) {
					fakeDir = std::make_shared<FakeDir>();
					fakeDynamicLibrary = std::make_shared<FakeDynamicLibrary>();
				}
public:
	TEST_METHOD(RunTest_HasTest_CheckRunTest) {
		TestExecutor testExecutor(fakeDir,fakeDynamicLibrary);
		TestCasePtr testCase = TestCasePtr(new TestCaseIgnored("Test", "IgnoreResult"));
		TestResult result = testExecutor.runTest(testCase).getResult();
		Assert::AreEqual<std::string>("Ignored", result.getCause());
	}


	TEST_METHOD(RunTests_HasTwoTests_CheckRunAllTests) {
		std::vector<TestReport> reports = actRunTestsFromTestCasesList();
		AssertRunAllTests(reports);
	}

	std::vector<darknessNight::CppUnitTestFramework::TestReport> actRunTestsFromTestCasesList() {
		TestExecutor testExecutor(fakeDir,fakeDynamicLibrary);
		TestCasePtr testCase = TestCasePtr(new TestCaseIgnored("Test", "IgnoreResult"));
		return testExecutor.runTests({ testCase, testCase });
	}

	void AssertRunAllTests(std::vector<darknessNight::CppUnitTestFramework::TestReport> &raports) {
		Assert::AreEqual<unsigned>(2, raports.size());
		for (auto rap : raports)
			Assert::AreEqual<std::string>("Ignored", rap.getResult().getCause());
	}


	TEST_METHOD(RunTests_HasTestSuite_CheckRunAllTests) {
		auto reports=actRunTestsTestSuite();
		AssertRunAllTests(reports);
	}
	std::vector<darknessNight::CppUnitTestFramework::TestReport> actRunTestsTestSuite() {
		TestExecutor testExecutor(fakeDir,fakeDynamicLibrary);
		TestSuite testSuite=prepareTestSuite();
		return testExecutor.runTests(TestSuitePtr(&testSuite, [](void*) {}));
	}

	darknessNight::CppUnitTestFramework::TestSuite prepareTestSuite() {
		TestSuite testSuite("Suite");
		addToTestSuiteTestCases(testSuite);
		return testSuite;
	}

	void addToTestSuiteTestCases(darknessNight::CppUnitTestFramework::TestSuite &testSuite) {
		TestCasePtr testCase1 = TestCasePtr(new TestCaseIgnored("Test", "IgnoreResult"));
		TestCasePtr testCase2 = TestCasePtr(new TestCaseIgnored("Test2", "IgnoreResult"));
		for (auto test : { testCase1, testCase2 })
			testSuite.addTestCase(test);
	}

	TEST_METHOD(RunTest_HasTestSuiteAndTestCaseName_CheckReturnReport) {
		TestSuite testSuite=prepareTestSuite();
		TestExecutor executor(fakeDir,fakeDynamicLibrary);
		auto report=executor.runTest(TestSuitePtr(&testSuite, [](void*) {}), "Test");
		Assert::AreEqual<std::string>("Test", report.getTestName());
	}

	TEST_METHOD(RunTest_HasPathAndFullTestName_CheckReturnReport) {
		prepareFakesForTestsDiscover();
		TestExecutor executor(fakeDir,fakeDynamicLibrary);
		auto reports = executor.runTests("Dll.dll", {"FullNamedTest(TestSuite)", "TrashName1", "TrashName2", "Second(TestSuite)"});
		assertHasFakeTestResults(reports);
	}

	void assertHasFakeTestResults(std::vector<darknessNight::CppUnitTestFramework::TestReport> &report) {
		auto firstName = report[0].getTestName();
		auto secondName = report[1].getTestName();
		Assert::IsTrue("FullNamedTest" == firstName || "FullNamedTest" == secondName);
		Assert::IsTrue("Second" == firstName || "Second" == secondName);
	}

	void prepareFakesForTestsDiscover() {
		fakeDynamicLibrary->dllFunc = []() {
			TestContainer* container = new TestContainer();
			container->addTestSuite(std::make_shared<TestSuiteCreator>("TestSuite"));
			container->registerTestCase("TestSuite", std::make_shared<TestCaseIgnored>("FullNamedTest", "Ignored"));
			container->registerTestCase("TestSuite", std::make_shared<TestCaseIgnored>("Second", "Ignored"));
			return container;
		};
	}

	TEST_METHOD(RunTestFromFile_HasCorrectPath_CheckReturnReports) {
		prepareFakesForTestsDiscover();
		TestExecutor executor(fakeDir,fakeDynamicLibrary);
		auto dir = Directory::Current();
		auto reports = executor.runTestsFromFile("Dll.dll");
		assertHasFakeTestResults(reports);
	}
			};
		}
	}
}