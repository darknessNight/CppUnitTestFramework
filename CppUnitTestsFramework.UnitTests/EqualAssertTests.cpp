#include "stdafx.h"
#include "AssertHelperClass.h"
#include <CppUnitTestsFramework\Assert.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {
	namespace CppUnitTestFramework {
		namespace UnitTests {
			TEST_CLASS(AssertEqualTests) {
public:
	TEST_METHOD(AreEqual_HasEqualObjects_CheckNoThrow) {
		try {
			darknessNight::CppUnitTestFramework::Assert::AreEqual(2, 2);
			darknessNight::CppUnitTestFramework::Assert::AreEqual(2.0, 2.0);
			darknessNight::CppUnitTestFramework::Assert::AreEqual(2U, 2U);
			darknessNight::CppUnitTestFramework::Assert::AreEqual("Elo", "Elo");
			darknessNight::CppUnitTestFramework::Assert::AreEqual(L"Elo", L"Elo");
			darknessNight::CppUnitTestFramework::Assert::AreEqual(AssertHelperClass(2), AssertHelperClass(2));
			darknessNight::CppUnitTestFramework::Assert::AreEqual(std::string("Elo"), std::string("Elo"));
		}
		catch (darknessNight::CppUnitTestFramework::AssertException) {
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
		}
	}

	TEST_METHOD(AreEqual_HasDiffObjects_CheckThrow) {
		checkAssertEqual(2, 3);
		checkAssertEqual(2, 3);
		checkAssertEqual(3.0, 2.0);
		checkAssertEqual(2U, 3U);
		checkAssertEqual("Elo", "Elo1");
		checkAssertEqual(L"Elo", L"Elo1");
		checkAssertEqual(AssertHelperClass(3), AssertHelperClass(2));
		checkAssertEqual(std::string("Elo"), std::string("Elo1"));
	}

	template <typename T> void checkAssertEqual(T val1, T val2) {
		try {
			darknessNight::CppUnitTestFramework::Assert::AreEqual(val1, val2);
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
		}
		catch (darknessNight::CppUnitTestFramework::AssertException) {
		}
	}

	TEST_METHOD(AreEqual_HasPointersToDiffObj_CheckThrow) {
		try {
			AssertHelperClass f(3), s(2);
			darknessNight::CppUnitTestFramework::Assert::AreEqualPtrValue(&f, &s);
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(L"No throw");
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
		}
	}

	TEST_METHOD(AreEqual_HasPointersToEqualObj_CheckNoThrow) {
		try {
			AssertHelperClass f(2), s(2);
			darknessNight::CppUnitTestFramework::Assert::AreEqualPtrValue(&f, &s);
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
		}
	}

	TEST_METHOD(AreEqual_HasDiffInt_CheckThrowExceptionWithValue) {
		try {
			darknessNight::CppUnitTestFramework::Assert::AreEqual(2, 3);
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(L"No throw");
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
			StringAssert::Constains("expected <2>", ex.getMessage(), L"No has correct expected part");
			StringAssert::Constains("was <3>", ex.getMessage(), L"No has correct result part");
		}
	}

	TEST_METHOD(AreEqual_HasDiffNoStringConvertableClass_CheckThrowExceptionWithValue) {
		try {
			darknessNight::CppUnitTestFramework::Assert::AreEqual(AssertHelperClass(2), AssertHelperClass(3));
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(L"No throw");
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
			StringAssert::Constains(std::string("expected <") + typeid(AssertHelperClass).name(), ex.getMessage(), L"No has correct expected part");
			StringAssert::Constains(std::string("was <") + typeid(AssertHelperClass).name(), ex.getMessage(), L"No has correct result part");
		}
	}

	TEST_METHOD(AreEqual_HasDiffIntAndMessage_CheckConstainsOwnMessage) {
		try {
			darknessNight::CppUnitTestFramework::Assert::AreEqual(AssertHelperClass(2), AssertHelperClass(3), "TestFailedMessage");
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(L"No throw");
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
			StringAssert::Constains(std::string("Message: <") + "TestFailedMessage>", ex.getMessage(), L"No has own message");
		}
	}

	TEST_METHOD(AreEqual_HasDoubleAndTolerance_CheckNoThrow) {
		try {
			darknessNight::CppUnitTestFramework::Assert::AreEqualWithTolerance(2.001, 2.0013, 0.001, "TestFailedMessage");
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
		}
	}

	TEST_METHOD(AreEqual_HasDoubleAndTolerance_CheckThrow) {
		try {
			darknessNight::CppUnitTestFramework::Assert::AreEqualWithTolerance(2.001, 2.0021, 0.001, "TestFailedMessage");
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
		}
	}

	TEST_METHOD(AreNotEqual_HasDoubleAndTolerance_CheckNoThrow) {
		try {
			darknessNight::CppUnitTestFramework::Assert::AreNotEqualWithTolerance(2.001, 2.0021, 0.001, "TestFailedMessage");
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
		}
	}

	TEST_METHOD(AreNotEqual_HasPointersToEqualObj_CheckThrow) {
		try {
			AssertHelperClass f(2), s(2);
			darknessNight::CppUnitTestFramework::Assert::AreNotEqualPtrValue(&f, &s);
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
		}
	}

	TEST_METHOD(AreNotEqual_HasDiffInt_CheckNoThrow) {
		try {
			darknessNight::CppUnitTestFramework::Assert::AreNotEqual(2, 3);
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
		}
	}

	TEST_METHOD(AreNotEqual_HasSameInt_CheckThrowAndHasMessage) {
		try {
			darknessNight::CppUnitTestFramework::Assert::AreNotEqual(2, 2, "Mess");
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
			StringAssert::Constains("Objects are equal", ex.getMessage());
			StringAssert::Constains(std::string("Message: <"), ex.getMessage(), L"No has own message");
		}
	}

	TEST_METHOD(AreNotSame_HasSameInt_CheckThrow) {
		try {
			int two = 2;
			darknessNight::CppUnitTestFramework::Assert::AreNotSame(two, two, "Mess");
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
		}
	}

	TEST_METHOD(AreNotSame_HasDiffInt_CheckNoThrow) {
		try {
			int two = 2;
			int three = 2;
			darknessNight::CppUnitTestFramework::Assert::AreNotSame(two, three, "Mess");
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
		}
	}

	TEST_METHOD(AreSame_HasSameInt_CheckThrow) {
		try {
			int two = 2;
			darknessNight::CppUnitTestFramework::Assert::AreSame(two, two, "Mess");
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
		}
	}

	TEST_METHOD(AreSame_HasDiffInt_CheckNoThrow) {
		try {
			int two = 2;
			int three = 2;
			darknessNight::CppUnitTestFramework::Assert::AreSame(two, three, "Mess");
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
		}
	}

	TEST_METHOD(AreSame_HasPtr_CheckNoFall) {
		try {
			int two = 2;
			int *ptr = &two;
			darknessNight::CppUnitTestFramework::Assert::AreSame(ptr, ptr, "Mess");
		}
		catch (darknessNight::CppUnitTestFramework::AssertException ex) {
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
		}
	}

			};
		}
	}
}