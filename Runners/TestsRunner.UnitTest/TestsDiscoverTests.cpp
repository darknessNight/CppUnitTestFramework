#include "stdafx.h"
#include "../TestsRunner/TestDiscover.h"
#include "FakeDynamicLibrary.h"
#include <CppUnitTestFramework/TestCaseIgnored.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {
	namespace TestsRunner {
		namespace UnitTest {

			TEST_CLASS(TestDiscoverTests) {
			private:
				std::shared_ptr<FakeDir> fakeDir;
				std::shared_ptr<FakeDynamicLibrary> fakeDynamicLibrary;
				std::shared_ptr<FakeLogger> fakeLogger;

				TEST_METHOD_INITIALIZE(SetUp) {
					fakeDir = std::make_shared<FakeDir>();
					fakeDynamicLibrary = std::make_shared<FakeDynamicLibrary>();
					fakeLogger = std::make_shared<FakeLogger>();
				}

				std::shared_ptr<TestDiscover> getTestObj() {
					return std::make_shared<TestDiscover>(fakeDir, fakeDynamicLibrary, *fakeLogger);
				}

				TEST_METHOD(FindAll_HasFakesDirectoryAndDllShared_CheckHasCorrectImportedTestCount) {
					auto discover=getTestObj();
					actDiscoverFindAll(*discover);
					Assert::AreEqual(2U, discover->getSuitesNames().size());
				}

				TEST_METHOD(FindAll_HasFakesDirectoryAndDllShared_CheckSendLogs) {
					prepareFakeDynamicLibraryToReturnTestCase();
					auto discover = getTestObj();
					actDiscoverFindAll(*discover);
					auto messages=fakeLogger->getMessages();
					int i = 0;
					assertStandardLogs(messages, i);
				}

				void assertStandardLogs(std::vector<std::string> &messages, int &i) {
					Assert::AreEqual<std::string>("M:DiscoverStarted", messages[i++]);
					Assert::AreEqual<std::string>("M:Has: <Dll.dll> Library loaded", messages[i++]);
					Assert::AreEqual<std::string>("M:Has: <Second.so> Library loaded", messages[i++]);
					Assert::AreEqual<std::string>("M:DiscoverEnded", messages[i++]);
					Assert::AreEqual<std::string>("M:Loaded tests: 2", messages[i++]);
				}

				void actDiscoverFindAll(darknessNight::TestsRunner::TestDiscover &discover) {
					discover.findAll({ "." }, { "dll","so" });
				}

				TEST_METHOD(FindAll_HasFakesDirectoryAndDllShared_CheckImportTestsFromDlls) {
					auto discover=getTestObj();
					actDiscoverFindAll(*discover);
					Assert::IsTrue(fakeDynamicLibrary->usedDll);
					Assert::IsTrue(fakeDynamicLibrary->usedSo);
				}

				TEST_METHOD(FindAll_HasFakeThrowedLoadLibraryException_CheckNoCollapse) {
					fakeDynamicLibrary->throwLibraryException = true;
					auto discover=getTestObj();
					actDiscoverFindAll(*discover);
					Assert::AreEqual<unsigned>(0, discover->getSuitesNames().size());
				}

				TEST_METHOD(FindAll_HasFakeThrowedFunctionLoadException_CheckNoCollapse) {
					fakeDynamicLibrary->throwFuncException = true;
					auto discover=getTestObj();
					actDiscoverFindAll(*discover);
					Assert::AreEqual<unsigned>(0, discover->getSuitesNames().size());
				}

				TEST_METHOD(FindAll_HasFakeReturnIncorrectLibVersion_CheckNoCollapse) {
					fakeDynamicLibrary->incorrectLibVer = true;
					auto discover = getTestObj();
					actDiscoverFindAll(*discover);
					Assert::AreEqual<unsigned>(0, discover->getSuitesNames().size());
				}

				TEST_METHOD(FindAll_HasFakes_CheckLoadSuites) {
					auto discover=getTestObj();
					actDiscoverFindAll(*discover);
					assertCorrectLoadSuites(*discover);
				}

				void assertCorrectLoadSuites(darknessNight::TestsRunner::TestDiscover &discover) {
					Assert::AreEqual<unsigned>(2, discover.getSuitesNames().size());
					Assert::AreEqual<std::string>("Unnamed", discover.getSuitesNames()[0]);
				}

				TEST_METHOD(GetTestsList_HasFakes_CheckReturnAllTestCases) {
					prepareFakes();
					auto discover=getTestObj();
					actDiscoverFindAll(*discover);
					assertGetCorrectTestsCount(*discover);
				}

				void prepareFakes() {
					prepareFakeDynamicLibraryToReturnTestCase();
					prepareFakeDirToReturnOneLibrary();
				}

				void assertGetCorrectTestsCount(darknessNight::TestsRunner::TestDiscover &discover) {
					Assert::AreEqual<unsigned>(1, discover.getTestsList().size());
				}

				void prepareFakeDirToReturnOneLibrary() {
					fakeDir->retEntries = { FakeEntry("Dll.dll") };
				}

				void prepareFakeDynamicLibraryToReturnTestCase() {
					fakeDynamicLibrary->dllFunc = []() {
						auto container= new TestContainer();
						TestCasePtr test = TestCasePtr(new TestCaseIgnored("IgnoredTest","Ignored"));
						container->registerTestCase("Unnamed", test);
						return  container;
					};
				}

				TEST_METHOD(GetTestsList_HasFakes_CheckIsCorrectCase) {
					prepareFakes();
					auto discover=getTestObj();
					actDiscoverFindAll(*discover);
					assertGetCorrectTest(*discover);
				}

				void assertGetCorrectTest(darknessNight::TestsRunner::TestDiscover &discover) {
					TestCasePtr test = discover.getTestsList()[0];
					Assert::AreEqual<std::string>("IgnoredTest(Unnamed)", test->getReportWithoutResult().getFullName());
				}

				TEST_METHOD(FindInFile_HasFake_CheckIsCorrectLoadedSuite) {
					auto discover=getTestObj();
					discover->findInFile("Dll.dll");
					Assert::AreEqual<unsigned>(1, discover->getSuitesNames().size());
				}
			};
		}
	}
}