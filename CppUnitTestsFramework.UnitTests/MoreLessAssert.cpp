#include "stdafx.h"
#include <CppUnitTestsFramework\GreaterLessAssert.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight_CppUnitTestFramework::UnitTests{
	TEST_CLASS(AssertGreaterLessTests)
	{
	public:
		TEST_METHOD(Greater_HasGreaterObject_CheckNoThrow){
			try {
				AssertGreaterLess::Greater(2, 3);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(Greater_HasEqualObject_CheckThrow) {
			try {
				AssertGreaterLess::Greater(3, 3);
				Assert::Fail(L"No throw");
			}
			catch (AssertException ex) {
				StringAssert::Constains("Result is to small", ex.getMessage());
			}
		}

		TEST_METHOD(Greater_HasSmallerObject_CheckThrow) {
			try {
				AssertGreaterLess::Greater(4, 3);
				Assert::Fail(L"No throw");
			}
			catch (AssertException ex) {
				StringAssert::Constains("Result is to small", ex.getMessage());
			}
		}

		TEST_METHOD(GreaterEqual_HasEqualAndGreaterObject_CheckThrow) {
			try {
				AssertGreaterLess::GreaterEqual(3, 4);
				AssertGreaterLess::GreaterEqual(3, 3);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(Less_HasLessObject_CheckNoThrow) {
			try {
				AssertGreaterLess::Less(3, 2);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(Less_HasEqualObject_CheckThrow) {
			try {
				AssertGreaterLess::Less(3, 3);
				Assert::Fail(L"No throw");
			}
			catch (AssertException ex) {
				StringAssert::Constains("Result is to big", ex.getMessage());
			}
		}

		TEST_METHOD(Less_HasSmallerObject_CheckThrow) {
			try {
				AssertGreaterLess::Less(3, 4);
				Assert::Fail(L"No throw");
			}
			catch (AssertException ex) {
				StringAssert::Constains("Result is to big", ex.getMessage());
			}
		}

		TEST_METHOD(LessEqual_HasEqualAndLessObject_CheckThrow) {
			try {
				AssertGreaterLess::LessEqual(4, 3);
				AssertGreaterLess::LessEqual(3, 3);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}
	};
}