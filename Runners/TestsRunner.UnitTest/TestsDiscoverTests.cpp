#include "stdafx.h"
#include "../TestsRunner/TestsDiscover.h"
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

				TEST_METHOD_INITIALIZE(SetUp) {
					fakeDir = std::make_shared<FakeDir>();
					DIContainer::Register<Directory>(fakeDir);
					fakeDynamicLibrary = std::make_shared<FakeDynamicLibrary>();
					DIContainer::Register<DynamicLibrary>(fakeDynamicLibrary);
				}

				TEST_METHOD(FindAll_HasFakesDirectoryAndDllShared_CheckHasCorrectImportedTestCount) {
					TestsDiscover discover;
					actDiscoverFindAll(discover);
					Assert::AreEqual(2U, discover.getSuitesNames().size());
				}

				void actDiscoverFindAll(darknessNight::TestsRunner::TestsDiscover &discover) {
					discover.findAll({ "." }, { "dll","so" });
				}

				TEST_METHOD(FindAll_HasFakesDirectoryAndDllShared_CheckImportTestsFromDlls) {
					TestsDiscover discover;
					actDiscoverFindAll(discover);
					Assert::IsTrue(fakeDynamicLibrary->usedDll);
					Assert::IsTrue(fakeDynamicLibrary->usedSo);
				}

				TEST_METHOD(FindAll_HasFakeThrowedLoadLibraryException_CheckNoCollapse) {
					fakeDynamicLibrary->throwLibraryException = true;
					TestsDiscover discover;
					actDiscoverFindAll(discover);
					Assert::AreEqual<unsigned>(0, discover.getSuitesNames().size());
				}

				TEST_METHOD(FindAll_HasFakeThrowedFunctionLoadException_CheckNoCollapse) {
					fakeDynamicLibrary->throwFuncException = true;
					TestsDiscover discover;
					actDiscoverFindAll(discover);
					Assert::AreEqual<unsigned>(0, discover.getSuitesNames().size());
				}

				TEST_METHOD(FindAll_HasFakes_CheckLoadSuites) {
					TestsDiscover discover;
					actDiscoverFindAll(discover);
					Assert::AreEqual<unsigned>(2, discover.getSuitesNames().size());
					Assert::AreEqual<std::string>("Unnamed", discover.getSuitesNames()[0]);
				}

				TEST_METHOD(GetTestsList_HasFakes_CheckReturnAllTestCases) {
					prepareFakeDynamicLibraryToReturnTestCase();
					prepareFakeDirToReturnOneLibrary();
					TestsDiscover discover;
					actDiscoverFindAll(discover);
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
					/*prepareFakeDynamicLibraryToReturnTestCase();
					prepareFakeDirToReturnOneLibrary();
					TestsDiscover discover;
					actDiscoverFindAll(discover);
					Assert::AreEqual<unsigned>(1, discover.getTestsList().size());*/
				}
			};
		}
	}
}