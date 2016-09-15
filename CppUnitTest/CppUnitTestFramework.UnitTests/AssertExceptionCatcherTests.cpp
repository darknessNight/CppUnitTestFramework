#include "stdafx.h"
#include <CppUnitTestFramework\AssertExceptionCatcher.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {
	namespace CppUnitTestFramework {
		namespace UnitTests {
			TEST_CLASS(AssertExceptionCatcherTests) {
public:
	TEST_METHOD(Throws_ThrowException_CheckCatchException) {
		auto testMethod = []() {throw std::runtime_error("Elo"); };
		try {
			AssertExceptionCatcher::Throws<std::exception>(testMethod);
		}
		catch (AssertFailException ex) {
			Assert::Fail();
		}
		catch (std::exception) {
			Assert::Fail();
		}
	}

	TEST_METHOD(Throws_ThrowException_CheckReturnException) {
		auto testMethod = []() {throw std::runtime_error("Elo"); };
		try {
			std::exception ex = AssertExceptionCatcher::Throws<std::exception>(testMethod);
			StringAssert::AreEqual("Elo", ex.what());
		}
		catch (AssertFailException ex) {
			Assert::Fail();
		}
		catch (std::exception) {
			Assert::Fail();
		}
	}

	TEST_METHOD(Throws_DoesNotThrowException_CheckThrowAssertFailException) {
		auto testMethod = []() {};
		try {
			std::exception ex = AssertExceptionCatcher::Throws<std::exception>(testMethod, "TestMessage");
			Assert::Fail();
		}
		catch (AssertFailException ex) {
			StringAssert::Constains("TestMessage", ex.getMessage());
			StringAssert::Constains("Exception not throwed", ex.getMessage());
		}
	}

	TEST_METHOD(Throws_DoesNotThrowException_CheckExceptionHasCause) {
		auto testMethod = []() {};
		try {
			std::exception ex = AssertExceptionCatcher::Throws<std::exception>(testMethod);
			Assert::Fail();
		}
		catch (AssertFailException ex) {
			StringAssert::Constains("Exception not throw", ex.getMessage());
		}
	}

	TEST_METHOD(Throws_DoesThrowWrongException_CheckExceptionHasCorrectCause) {
		auto testMethod = []() {throw std::runtime_error(""); };
		try {
			std::exception ex = AssertExceptionCatcher::Throws<AssertPassException>(testMethod, "TestMessage");
			Assert::Fail();
		}
		catch (AssertFailException ex) {
			StringAssert::Constains("TestMessage", ex.getMessage());
			StringAssert::Constains("Wrong exception throwed", ex.getMessage(), L"BasicMessage");
			StringAssert::Constains(std::string("Catched <") + typeid(std::runtime_error).name() + ">", ex.getMessage(), L"WhatCatch");
			StringAssert::Constains(std::string("but expected <") + typeid(AssertPassException).name() + ">", ex.getMessage(), L"WhatExpect");
		}
	}

	TEST_METHOD(Throws_DoesThrowString_CheckExceptionHasCorrectCause) {
		auto testMethod = []() {throw "Hello"; };
		try {
			std::exception ex = AssertExceptionCatcher::Throws<AssertPassException>(testMethod);
			Assert::Fail();
		}
		catch (AssertFailException ex) {
			StringAssert::Constains("Catched unexpected exception <Unknow-Type>", ex.getMessage());
		}
	}

	TEST_METHOD(DoesNotThrow_DoesNotThrowException_CheckNoThrow) {
		auto testMethod = []() {};
		try {
			AssertExceptionCatcher::DoesNotThrow(testMethod);
		}
		catch (AssertFailException ex) {
			Assert::Fail();
		}
		catch (std::exception) {
			Assert::Fail();
		}
	}

	TEST_METHOD(DoesNotThrow_DoesThrowException_CheckThrowAndHasMessage) {
		auto testMethod = []() {throw std::runtime_error(""); };
		try {
			AssertExceptionCatcher::DoesNotThrow(testMethod, "TestMessage");
			Assert::Fail();
		}
		catch (AssertFailException ex) {
			StringAssert::Constains("TestMessage", ex.getMessage());
			StringAssert::Constains("Catched unexpected exception", ex.getMessage());
			StringAssert::Constains("<" + std::string(typeid(std::exception).name()) + ">", ex.getMessage());
		}
		catch (std::exception) {
			Assert::Fail();
		}
	}

	TEST_METHOD(DoesNotThrow_DoesThrowString_CheckThrowAndHasMessage) {
		auto testMethod = []() {throw "Elo"; };
		try {
			AssertExceptionCatcher::DoesNotThrow(testMethod);
			Assert::Fail();
		}
		catch (AssertFailException ex) {
			StringAssert::Constains("Catched unexpected exception", ex.getMessage());
			StringAssert::Constains("<Unknow-Type>", ex.getMessage());
		}
		catch (std::exception ex) {
			Assert::Fail();
		}
	}
			};
		}
	}
}