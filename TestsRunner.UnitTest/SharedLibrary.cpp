#include "stdafx.h"
#include "CppUnitTest.h"
#include "../TestsRunner/SharedLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight_SharedLibrary::IntegrationTests{		
	TEST_CLASS(SharedLibraryTest){
	public:
		
		TEST_METHOD(Import_HasCorrectNames_CheckReturnFunc){
			auto result = SharedLibrary::importFunction<void*()>("CppUnitTestFrameworkExamples.dll", "getTestsFromDynamicTestsLibrary");
			Assert::IsTrue(result!=nullptr);
		}

		TEST_METHOD(Import_HasCorrectLibraryNameAndIncorrectFuncName_CheckThrow) {
			try {
				SharedLibrary::importFunction<void*()>("CppUnitTestFrameworkExamples.dll", "NoExistsFunc");
				Assert::Fail();
			}
			catch (FunctionLoadException ex) {
				Assert::AreEqual(std::string("Not found function: NoExistsFunc"), ex.getMessage());
			}
		}

		TEST_METHOD(Import_HasIncorrectLibraryName_CheckThrow) {
			try {
				SharedLibrary::importFunction<void*()>("NoExistsLibrary.dll", "NoExistsFunc");
				Assert::Fail();
			}
			catch (LibraryLoadException ex) {
				Assert::AreEqual(std::string("Cannot load library: NoExistsLibrary.dll"), ex.getMessage());
			}
		}

		TEST_METHOD(FreeLibrary_HasIncorrectLibraryName_CheckNoThrow) {
			try {
				SharedLibrary::freeLibrary("NoExistsLibrary.dll");
			}
			catch (...) {
				Assert::Fail();
			}
		}

	};
}