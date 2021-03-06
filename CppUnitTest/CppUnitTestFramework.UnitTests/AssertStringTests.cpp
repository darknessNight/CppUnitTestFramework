#include "stdafx.h"
#include <CppUnitTestFramework\AssertString.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {
	namespace CppUnitTestFramework {
		namespace UnitTests {
			TEST_CLASS(AssertStringTests) {
public:
	TEST_METHOD(AreEqualIgnoringCase_HasTwoEqualIgnoringCaseString_CheckNoThrow) {
		try {
			AssertString::AreEqualIgnoringCase("TestForEvery", "TeStFoReVeRy");
			AssertString::AreEqualIgnoringCase("TestForEvery", "TestForEvery");
		}
		catch (...) {
			Assert::Fail();
		}
	}

	TEST_METHOD(AreEqualIgnoringCase_HasTwoDiffIgnoringCaseString_CheckThrow) {
		try {
			AssertString::AreEqualIgnoringCase("TestForEvery", "TestForEvery1");
			Assert::Fail();
		}
		catch (...) {
		}
	}

	TEST_METHOD(AreNotEqualIgnoringCase_HasTwoDiffIgnoringCaseString_CheckNoThrow) {
		try {
			AssertString::AreNotEqualIgnoringCase("TestForEvery", "TestForEvery1");
		}
		catch (...) {
			Assert::Fail();
		}
	}

	TEST_METHOD(Contains_HasContainsStrings_CheckNoThrow) {
		try {
			AssertString::Contains("Test", "TestForEvery");
		}
		catch (...) {
			Assert::Fail();
		}
	}

	TEST_METHOD(Contains_HasNotContainsStrings_CheckThrow) {
		try {
			AssertString::Contains("Test1", "TestForEvery");
			Assert::Fail();
		}
		catch (AssertFailException ex) {
			StringAssert::Constains("Not found <Test1> in <TestForEvery>", ex.getMessage());
		}
	}

	TEST_METHOD(NotContains_HasContainsStrings_CheckThrow) {
		try {
			AssertString::NotContains("Test", "TestForEvery");
			Assert::Fail();
		}
		catch (AssertFailException ex) {
			StringAssert::Constains("Found <Test> in <TestForEvery>", ex.getMessage());
		}
	}

	TEST_METHOD(EndsWith_HasEndsWithStrings_CheckNoThrow) {
		try {
			AssertString::EndsWith("Every", "TestForEvery");
		}
		catch (...) {
			Assert::Fail();
		}
	}

	TEST_METHOD(EndsWith_HasNotEndsWithStrings_CheckThrow) {
		try {
			AssertString::EndsWith("Test1", "TestForEvery");
			Assert::Fail();
		}
		catch (AssertFailException ex) {
			StringAssert::Constains("<TestForEvery> does not end with <Test1>", ex.getMessage());
		}
	}

	TEST_METHOD(NotEndsWith_HasEndsWithStrings_CheckThrow) {
		try {
			AssertString::DoesNotEndWith("Every", "TestForEvery");
			Assert::Fail();
		}
		catch (AssertFailException ex) {
			StringAssert::Constains("<TestForEvery> ends with <Every>", ex.getMessage());
		}
	}

	TEST_METHOD(StartsWith_HasStartsWithStrings_CheckNoThrow) {
		try {
			AssertString::StartsWith("Test", "TestForEvery");
		}
		catch (...) {
			Assert::Fail();
		}
	}

	TEST_METHOD(StartsWith_HasNotStartsWithStrings_CheckThrow) {
		try {
			AssertString::StartsWith("Test1", "TestForEvery");
			Assert::Fail();
		}
		catch (AssertFailException ex) {
			StringAssert::Constains("<TestForEvery> does not start with <Test1>", ex.getMessage());
		}
	}

	TEST_METHOD(NotStartsWith_HasStartsWithStrings_CheckThrow) {
		try {
			AssertString::DoesNotStartWith("Test", "TestForEvery");
			Assert::Fail();
		}
		catch (AssertFailException ex) {
			StringAssert::Constains("<TestForEvery> starts with <Test>", ex.getMessage());
		}
	}

	TEST_METHOD(Match_HasMatchStrings_CheckNoThrow) {
		try {
			AssertString::Match("Test...[0-9]{1,2}Ev[eE]ry", "TestFor12Every");
		}
		catch (...) {
			Assert::Fail();
		}
	}

	TEST_METHOD(Match_HasNotMatchStrings_CheckThrow) {
		try {
			AssertString::Match("Test...[0-9]{1,2}Ev[eE]ry", "TestForASAvery");
			Assert::Fail();
		}
		catch (AssertFailException ex) {
			StringAssert::Constains("<TestForASAvery> does not match <Test...[0-9]{1,2}Ev[eE]ry>", ex.getMessage());
		}
	}

	TEST_METHOD(NotMatch_HasMatchStrings_CheckThrow) {
		try {
			AssertString::DoesNotMatch("Test...[0-9]{1,2}Ev[eE]ry", "TestFor12Every");
			Assert::Fail();
		}
		catch (AssertFailException ex) {
			StringAssert::Constains("<TestFor12Every> match <Test...[0-9]{1,2}Ev[eE]ry>", ex.getMessage());
		}
	}
			};
		}
	}
}