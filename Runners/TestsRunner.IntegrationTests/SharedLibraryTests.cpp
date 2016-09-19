#include "stdafx.h"
#include "CppUnitTest.h"
#include "../TestsRunner/SharedLibrary/SharedLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern "C" {
	__declspec(dllexport)
		void* getTestsFromDynamicTestsLibrary() {
		return nullptr;
	}
}

namespace darknessNight {
	namespace SharedLibrary {
		namespace IntegrationTests {
			TEST_CLASS(SharedLibraryTest) {
public:

	TEST_METHOD(Import_HasCorrectNames_CheckReturnFunc) {
		try {
			DynamicLibrary lib;
			auto result = lib.importFunction<void*()>("TestsRunner.IntegrationTests.dll", "getTestsFromDynamicTestsLibrary");
			lib.freeLibrary("TestsRunner.IntegrationTests.dll");
			Assert::IsTrue(result != nullptr);
		}
		catch (Exception ex) {
			std::string nstr = ex.getMessage();
			std::wstring wstr(nstr.begin(), nstr.end());
			Assert::Fail(wstr.c_str());
		}
	}

	TEST_METHOD(Import_HasCorrectLibraryNameAndIncorrectFuncName_CheckThrow) {
		try {
			DynamicLibrary lib;
			lib.importFunction<void*()>("TestsRunner.IntegrationTests.dll", "NoExistsFunc");
			lib.freeLibrary("TestsRunner.IntegrationTests.dll");
			Assert::Fail();
		}
		catch (FunctionLoadException ex) {
			Assert::AreEqual(std::string("Not found function: NoExistsFunc"), ex.getMessage());
		}
	}

	TEST_METHOD(Import_HasIncorrectLibraryName_CheckThrow) {
		try {
			DynamicLibrary lib;
			lib.importFunction<void*()>("NoExistsLibrary.dll", "NoExistsFunc");
			Assert::Fail();
		}
		catch (LibraryLoadException ex) {
			Assert::AreEqual(std::string("Cannot load library: NoExistsLibrary.dll"), ex.getMessage());
		}
	}

	TEST_METHOD(FreeLibrary_HasIncorrectLibraryName_CheckNoThrow) {
		try {
			DynamicLibrary lib;
			lib.freeLibrary("NoExistsLibrary.dll");
		}
		catch (...) {
			Assert::Fail();
		}
	}

			};
		}
	}
}