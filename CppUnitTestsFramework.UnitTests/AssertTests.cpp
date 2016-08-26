#include "stdafx.h"
#include <CppUnitTestsFramework\Asserts.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight_CppUnitTestFramework::UnitTests {
	class HelperClass {
	private:
		int val;
	public:
		HelperClass(int v) {
			val = v;
		}
		bool operator==(const HelperClass& rhs) const {
			return val == rhs.val;
		}
	};
	TEST_CLASS(AssertTests)
	{
	public:
		TEST_METHOD(AreEqual_HasEqualObjects_CheckNoThrow) {
			try {
				darknessNight_CppUnitTestFramework::Assert::AreEqual(2, 2);
				darknessNight_CppUnitTestFramework::Assert::AreEqual(2.0, 2.0);
				darknessNight_CppUnitTestFramework::Assert::AreEqual(2U, 2U);
				darknessNight_CppUnitTestFramework::Assert::AreEqual("Elo", "Elo");
				darknessNight_CppUnitTestFramework::Assert::AreEqual(L"Elo", L"Elo");
				darknessNight_CppUnitTestFramework::Assert::AreEqual(HelperClass(2), HelperClass(2));
				darknessNight_CppUnitTestFramework::Assert::AreEqual(std::string("Elo"), std::string("Elo"));
			}
			catch (darknessNight_CppUnitTestFramework::AssertException) {
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
			checkAssertEqual(HelperClass(3), HelperClass(2));
			checkAssertEqual(std::string("Elo"), std::string("Elo1"));
		}

		template <typename T> void checkAssertEqual(T val1, T val2) {
			try {
				darknessNight_CppUnitTestFramework::Assert::AreEqual(val1, val2);
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
			}
			catch (darknessNight_CppUnitTestFramework::AssertException) {
			}
		}

		TEST_METHOD(AreEqual_HasPointersToDiffObj_CheckThrow) {
			try {
				HelperClass f(3), s(2);
				darknessNight_CppUnitTestFramework::Assert::AreEqualPtrValue(&f, &s);
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(L"No throw");
			}
			catch (darknessNight_CppUnitTestFramework::AssertException ex) {
			}
		}

		TEST_METHOD(AreEqual_HasPointersToEqualObj_CheckNoThrow) {
			try {
				HelperClass f(2), s(2);
				darknessNight_CppUnitTestFramework::Assert::AreEqualPtrValue(&f, &s);
			}
			catch (darknessNight_CppUnitTestFramework::AssertException ex) {
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
			}
		}

		TEST_METHOD(AreEqual_HasDiffInt_CheckThrowExceptionWithValue) {
			try {
				darknessNight_CppUnitTestFramework::Assert::AreEqual(2, 3);
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(L"No throw");
			}
			catch (darknessNight_CppUnitTestFramework::AssertException ex) {
				StringAssert::Constains("expected <2>", ex.getMessage(), L"No has correct expected part");
				StringAssert::Constains("received <3>", ex.getMessage(), L"No has correct result part");
			}
		}

		TEST_METHOD(AreEqual_HasDiffNoStringConvertableClass_CheckThrowExceptionWithValue) {
			try {
				darknessNight_CppUnitTestFramework::Assert::AreEqual(HelperClass(2), HelperClass(3));
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(L"No throw");
			}
			catch (darknessNight_CppUnitTestFramework::AssertException ex) {
				StringAssert::Constains(std::string("expected <")+typeid(HelperClass).name(), ex.getMessage(), L"No has correct expected part");
				StringAssert::Constains(std::string("received <")+typeid(HelperClass).name(), ex.getMessage(), L"No has correct result part");
			}
		}

		TEST_METHOD(AreEqual_HasDiffIntAndMessage_CheckConstainsOwnMessage) {
			try {
				darknessNight_CppUnitTestFramework::Assert::AreEqual(HelperClass(2), HelperClass(3), "TestFailedMessage");
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(L"No throw");
			}
			catch (darknessNight_CppUnitTestFramework::AssertException ex) {
				StringAssert::Constains(std::string("Message: <") + "TestFailedMessage>", ex.getMessage(), L"No has own message");
			}
		}

		TEST_METHOD(AreEqual_HasDoubleAndTolerance_CheckNoThrow) {
			try {
				darknessNight_CppUnitTestFramework::Assert::AreEqual(2.001, 2.0013,0.001, "TestFailedMessage");
			}
			catch (darknessNight_CppUnitTestFramework::AssertException ex) {
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
			}
		}

		TEST_METHOD(AreEqual_HasDoubleAndTolerance_CheckThrow) {
			try {
				darknessNight_CppUnitTestFramework::Assert::AreEqual(2.001, 2.0021, 0.001, "TestFailedMessage");
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
			}
			catch (darknessNight_CppUnitTestFramework::AssertException ex) {
			}
		}

		TEST_METHOD(AreNotEqual_HasDoubleAndTolerance_CheckNoThrow) {
			try {
				darknessNight_CppUnitTestFramework::Assert::AreNotEqual(2.001, 2.0021, 0.001, "TestFailedMessage");
			}
			catch (darknessNight_CppUnitTestFramework::AssertException ex) {
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
			}
		}

		TEST_METHOD(AreNotEqual_HasPointersToEqualObj_CheckThrow) {
			try {
				HelperClass f(2), s(2);
				darknessNight_CppUnitTestFramework::Assert::AreNotEqualPtrValue(&f, &s);
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
			}
			catch (darknessNight_CppUnitTestFramework::AssertException ex) {
			}
		}

		TEST_METHOD(AreNotEqual_HasDiffInt_CheckNoThrow) {
			try {
				darknessNight_CppUnitTestFramework::Assert::AreNotEqual(2, 3);
			}
			catch (darknessNight_CppUnitTestFramework::AssertException ex) {
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
			}
		}

		TEST_METHOD(AreNotEqual_HasSameInt_CheckThrowAndHasMessage) {
			try {
				darknessNight_CppUnitTestFramework::Assert::AreNotEqual(2, 2, "Mess");
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
			}
			catch (darknessNight_CppUnitTestFramework::AssertException ex) {
				StringAssert::Constains("Object is same", ex.getMessage());
				StringAssert::Constains(std::string("Message: <"), ex.getMessage(), L"No has own message");
			}
		}

	};
}