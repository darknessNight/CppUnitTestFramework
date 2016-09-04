#include "stdafx.h"
#include "../TestsRunner/TestsDiscover.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {
	namespace TestsRunner {
		namespace UnitTest {
			using namespace Filesystem;
			
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
				virtual std::shared_ptr<Directory> get(std::string path) override {
					return std::make_shared<FakeDir>();
				}
				virtual std::vector<Entry> getElements() override {
					return std::vector<Entry>();
				}
				virtual std::vector<Entry> getElementsRecursive() override {
					return std::vector<Entry>();
				}
				virtual std::vector<Entry> searchElements(std::string pattern) override {
					return std::vector<Entry>({FakeEntry("Dll.dll"), FakeEntry("Second.so")});
				}
			};

			TEST_CLASS(TestDiscoverTests) {
				TEST_METHOD_INITIALIZE(SetUp) {
					DIContainer::Register<Directory, FakeDir>();
				}

				TEST_METHOD(FindAll_HasFakesDirectoryAndDllShared_CheckHasCorrectImportedTestCount) {
					TestsDiscover discover;
					discover.findAll({ "./*" }, { ".dll",".so" });
					Assert::AreEqual(2U, discover.getSuites().size());
				}

				TEST_METHOD(FindAll_HasFakesDirectoryAndDllShared_CheckImportTestsFromDlls) {
					TestsDiscover discover;
					discover.findAll({ "./*" }, { ".dll",".so" });
					Assert::AreEqual(2U, discover.getSuites().size());
				}
			};
		}
	}
}