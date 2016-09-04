#include "stdafx.h"
#include "../TestsRunner/TestsDiscover.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {
	namespace TestsRunner {
		namespace UnitTest {
			using namespace Filesystem;
			

			TEST_CLASS(TestDiscoverTests) {
				TEST_METHOD_INITIALIZE(SetUp) {
					//DIContainer::Register<IDirectory, FakeDir>();
				}

				TEST_METHOD(FindAllTestsDll_HasFakesDirectoryAndDllShared_CheckImportAllTests) {
					TestsDiscover discover;
					discover.findAll({ "./*" }, { ".dll",".so" });
					Assert::AreEqual(2U, discover.getSuites().size());
				}
			};
		}
	}
}