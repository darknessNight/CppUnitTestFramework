#include "stdafx.h"
#include "../TestsRunner/TestsDiscover.h"
#include <CppUnitTestFramework/TestCaseIgnored.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {
	namespace TestsRunner {
		namespace UnitTest {
			using namespace Filesystem;
			using namespace SharedLibrary;

			class FakeEntry :public Entry {
			public:
				FakeEntry() {
				}

				FakeEntry(std::string p) {
					setPath(p);
				}

				void setPath(std::string p) {
					path = p;
				}
			};

			class FakeDir :public Directory {
				// Inherited via IDirectory
			public:
				std::vector<Entry> retEntries= { FakeEntry("Dll.dll"), FakeEntry("Second.so") };
				virtual std::shared_ptr<Directory> get(std::string path) override {
					auto ptr = std::make_shared<FakeDir>();
					ptr->retEntries = retEntries;
					return ptr;
				}
				virtual std::vector<Entry> getElements() override {
					return std::vector<Entry>();
				}
				virtual std::vector<Entry> getElementsRecursive() override {
					return std::vector<Entry>();
				}
				virtual std::vector<Entry> searchElements(std::string pattern) override {
					if (pattern == ".*/.*\\.(dll|so)")
						return retEntries;
					else return std::vector<Entry>();
				}
			};

			class FakeDynamicLibrary : public DynamicLibrary {
			public:
				bool usedDll = false;
				bool usedSo = false;
				bool throwLibraryException = false;
				bool throwFuncException = false;
				TestContainer*(*dllFunc)() = &FakeDynamicLibrary::getTestSuites;
			protected:
				virtual void* getFunction(std::string &module, std::string &func) override {
					throwIfSetted();
					checkHasCorrectLibrary(module);
					return returnFuncIfNameIsCorrect(func);
				}
				void throwIfSetted() {
					if (throwLibraryException)
						throw LibraryLoadException("");
					if (throwFuncException)
						throw FunctionLoadException("");
				}

				void * returnFuncIfNameIsCorrect(std::string & func) {
					if (func == "getTestsFromDynamicTestsLibrary")
						return dllFunc;
					else {
						throw FunctionLoadException("");
					}
				}
				void checkHasCorrectLibrary(std::string & module) {
					if (module == "Dll.dll")
						usedDll = true;
					else
						if (module == "Second.so")
							usedSo = true;
						else
							throw LibraryLoadException("");
				}

				static TestContainer* getTestSuites() {
					return new TestContainer();
				}
			};

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
			};
		}
	}
}