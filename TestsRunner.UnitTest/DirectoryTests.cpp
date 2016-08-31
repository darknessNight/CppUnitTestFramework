#include "stdafx.h"
#include "../TestsRunner/Directory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {
	namespace FileSystem {
		namespace IntegrationTests {
			TEST_CLASS(DirectoryTests) {
public:
	TEST_METHOD(GetCurrentDirectory_CheckReturnCorrectDir) {
		Directory dir=Directory::Current();
		std::string path= dir.getPath();
		bool result = (int)path.find("CppUnitTestsFramework") >= 0;
		Assert::IsTrue(result);
	}
			};
		}
	}
}