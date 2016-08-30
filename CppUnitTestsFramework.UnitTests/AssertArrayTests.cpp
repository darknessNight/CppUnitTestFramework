#include "stdafx.h"
#include <CppUnitTestsFramework\AssertArray.h>
#include <vector>
#include <array>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight_CppUnitTestFramework::UnitTests {
	TEST_CLASS(AssertArrayTests)
	{
	public:
		TEST_METHOD(AreEqual_HasSameVector_CheckNoThrow) {
			std::vector<int> testArray = { 1,2,3,4,5,6,7,8 };
			try {
				AssertArray::AreEqual(testArray, testArray);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(AreEqual_HasDiffVector_CheckThrow) {
			std::vector<int> testArray = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray2 = { 0,2,3,4,5,6,7,8 };
			try {
				AssertArray::AreEqual(testArray, testArray2, "TestMessage");
				Assert::Fail();
			}
			catch (AssertException ex) {
				StringAssert::Constains("TestMessage", ex.getMessage(), L"userMessage");
				StringAssert::Constains("Expected", ex.getMessage(), L"assertMessage");
			}
		}

		TEST_METHOD(AreEqual_HasDiffLenghtVector_CheckThrow) {
			std::vector<int> testArray = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray2 = { 1,2,3,4,5,6,7 };
			try {
				AssertArray::AreEqual(testArray, testArray2);
				Assert::Fail();
			}
			catch (AssertException ex) {
			}
		}

		TEST_METHOD(AreEqual_HasCArray_CheckThrow) {
			int testArray[] = { 1,2,3,4,5,6,7,8 };
			int testArray2[] = { 1,2,3,4,5,6,7, 9 };
			try {
				AssertArray::AreEqual(testArray, 8, testArray2, 8);
				Assert::Fail();
			}
			catch (AssertException ex) {
			}
		}

		TEST_METHOD(AreEqual_HasCArrayDiffLen_CheckThrow) {
			int testArray[] = { 1,2,3,4,5,6,7,8 };
			int testArray2[] = { 1,2,3,4,5,6 };
			try {
				AssertArray::AreEqual(testArray, 8, testArray2, 6);
				Assert::Fail();
			}
			catch (AssertException ex) {
			}
		}

		TEST_METHOD(AreNotEqual_HasSameVector_CheckThrow) {
			std::vector<int> testArray = { 1,2,3,4,5,6,7,8 };
			try {
				AssertArray::AreNotEqual(testArray, testArray, "TestMessage");
				Assert::Fail();
			}
			catch (AssertException ex) {
				StringAssert::Constains("TestMessage", ex.getMessage(), L"userMessage");
				StringAssert::Constains("Arrays are equal", ex.getMessage(), L"assertMessage");
			}
		}

		TEST_METHOD(AreNotEqual_HasCArray_CheckThrow) {
			int testArray[] = { 1,2,3,4,5,6,7,8 };
			try {
				AssertArray::AreNotEqual(testArray, 8, testArray, 8);
				Assert::Fail();
			}
			catch (AssertException ex) {
			}
		}

		TEST_METHOD(AreEquivalent_HasSameVector_CheckNoThrow) {
			std::vector<int> testArray = { 1,2,3,4,5,6,7,8 };
			try {
				AssertArray::AreEquivalent(testArray, testArray);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(AreEquivalent_HasSameUnorderedVector_CheckNoThrow) {
			std::vector<int> testArray = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray2 = { 4,5,6,7,8, 1,2,3 };
			try {
				AssertArray::AreEquivalent(testArray, testArray2);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(AreEquivalent_HasDiffVector_CheckThrow) {
			std::vector<int> testArray = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray2 = { 4,5,6,7,8, 1,2,4 };
			try {
				AssertArray::AreEquivalent(testArray, testArray2, "TestMessage");
				Assert::Fail();
			}
			catch (AssertException ex) {
				StringAssert::Constains("TestMessage", ex.getMessage(), L"userMessage");
				StringAssert::Constains("Expected", ex.getMessage(), L"assertMessage");
			}
		}

		TEST_METHOD(AreEquivalent_HasSameUnorderedCArray_CheckNoThrow) {
			int testArray[] = { 1,2,3,4,5,6,7,8 };
			int testArray2[] = { 4,5,6,7,8, 1,2,3 };
			try {
				AssertArray::AreEquivalent(testArray, 8, testArray2, 8);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(AreNotEquivalent_HasSameUnorderedVector_CheckThrow) {
			std::vector<int> testArray = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray2 = { 4,5,6,7,8, 1,2,3 };
			try {
				AssertArray::AreNotEquivalent(testArray, testArray2, "TestMessage");
				Assert::Fail();
			}
			catch (AssertException ex) {
				StringAssert::Constains("TestMessage", ex.getMessage(), L"userMessage");
				StringAssert::Constains("Arrays are equivalent", ex.getMessage(), L"assertMessage");
			}
		}

		TEST_METHOD(Constains_HasCoinstainsVector_CheckNoThrow) {
			std::vector<int> testArray = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray2 = { 1,4,5,6,7,2,3 };
			try {
				AssertArray::Contains(testArray2, testArray);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(Constains_HasNonCoinstainsVector_CheckThrow) {
			std::vector<int> testArray2 = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray = { 1,4,5,6,0,2,3 };
			try {
				AssertArray::Contains(testArray, testArray2, "TestMessage");
				Assert::Fail();
			}
			catch (AssertException ex) {
				StringAssert::Constains("TestMessage", ex.getMessage(), L"userMessage");
				StringAssert::Constains("Expected constains", ex.getMessage(), L"assertMessage");
			}
		}

		TEST_METHOD(DoesNotConstain_HasCoinstainsVector_CheckThrow) {
			std::vector<int> testArray2 = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray = { 1,4,5,6,7,2,3 };
			try {
				AssertArray::DoesNotContain(testArray, testArray2, "TestMessage");
				Assert::Fail();
			}
			catch (AssertException ex) {
				StringAssert::Constains("TestMessage", ex.getMessage(), L"userMessage");
				StringAssert::Constains("Result array constains expected array", ex.getMessage(), L"assertMessage");
			}
		}

		TEST_METHOD(Constains_HasCoinstainsCArray_CheckNoThrow) {
			int testArray2[] = { 1,2,3,4,5,6,7,8 };
			int testArray[] = { 1,4,5,6,7,2,3 };
			try {
				AssertArray::Contains(testArray, 7, testArray2, 8);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(IsSubsequence_HasSubsequenceVector_CheckNoThrow) {
			std::vector<int> testArray = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray2 = { 1,2,3,4,5,6,7 };
			try {
				AssertArray::IsSubsequence(testArray2, testArray);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(IsSubsequence_HasNonSubsequenceVector_CheckThrow) {
			std::vector<int> testArray2 = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray = { 1,2,3,4,5,6,0 };
			try {
				AssertArray::IsSubsequence(testArray, testArray2, "TestMessage");
				Assert::Fail();
			}
			catch (AssertException ex) {
				StringAssert::Constains("TestMessage", ex.getMessage(), L"userMessage");
				StringAssert::Constains("> has not subsequence <", ex.getMessage(), L"assertMessage");
			}
		}

		TEST_METHOD(IsNotSubsequence_HasSubsequenceVector_CheckThrow) {
			std::vector<int> testArray2 = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray = { 2,3,4,5,6,7, 8 };
			try {
				AssertArray::IsNotSubsequence(testArray, testArray2, "TestMessage");
				Assert::Fail();
			}
			catch (AssertException ex) {
				StringAssert::Constains("TestMessage", ex.getMessage(), L"userMessage");
				StringAssert::Constains("> has subsequence <", ex.getMessage(), L"assertMessage");
			}
		}

		TEST_METHOD(IsSubsequence_HasSubsequenceCArray_CheckNoThrow) {
			int testArray2[] = { 1,2,3,4,5,6,7,8 };
			int testArray[] = { 1,2,3,4,5,6,7 };
			try {
				AssertArray::IsSubsequence(testArray, 7, testArray2, 8);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(IsOrdered_HasOrderedCArray_CheckNoThrow) {
			int testArray[] = { 1,2,3,4,5,6,7,8 };
			try {
				AssertArray::IsOrdered(testArray, 8);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(IsOrdered_HasOrderedVector_CheckNoThrow) {
			std::vector<int> testArray = { 1,2,3,4,5,6,7,8 };
			try {
				AssertArray::IsOrdered(testArray);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(IsOrdered_HasUnorderedVector_CheckThrow) {
			std::vector<int> testArray = { 1,2,3,4,6, 5,7,8 };
			try {
				AssertArray::IsOrdered(testArray, "TestMessage");
				Assert::Fail();
			}
			catch (AssertException ex) {
				StringAssert::Constains("TestMessage", ex.getMessage(), L"userMessage");
				StringAssert::Constains("> is not ordered", ex.getMessage(), L"assertMessage");
			}
		}

		TEST_METHOD(IsNotOrdered_HasOrderedVector_CheckThrow) {
			std::vector<int> testArray = { 1,2,3,4,5,6,7,8 };
			try {
				AssertArray::IsNotOrdered(testArray, "TestMessage");
				Assert::Fail();
			}
			catch (AssertException ex) {
				StringAssert::Constains("TestMessage", ex.getMessage(), L"userMessage");
				StringAssert::Constains("> is ordered", ex.getMessage(), L"assertMessage");
			}
		}

		TEST_METHOD(AllItemsAre_HasCorrectCArray_CheckNoThrow) {
			const int testArray[] = { 0,2,3,4,5,6,7,8 };
			auto itemIsNotOne = [](const int* item){return *item != 1; };
			try {
				AssertArray::AllItemsAre<int>(testArray, 8, itemIsNotOne);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(AllItemsAre_HasCorrectVector_CheckNoThrow) {
			std::vector<int> testArray = { 0,2,3,4,5,6,7,8 };
			auto itemIsNotOne = [](std::vector<int>::const_iterator item) {return *item != 1; };
			try {
				AssertArray::AllItemsAre(testArray, itemIsNotOne);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(AllItemsAre_HasUncorrectVector_CheckThrow) {
			std::vector<int> testArray = { 0,2,3,4,6, 5,7,1 };
			auto itemIsNotOne = [](std::vector<int>::const_iterator item) {return *item != 1; };
			try {
				AssertArray::AllItemsAre(testArray, itemIsNotOne, "TestMessage");
				Assert::Fail();
			}
			catch (AssertException ex) {
				StringAssert::Constains("TestMessage", ex.getMessage(), L"userMessage");
				StringAssert::Constains("> items not satisfy a predicate", ex.getMessage(), L"assertMessage");
			}
		}
		
		TEST_METHOD(AllItemsAreUnique_HasCorrectCArray_CheckNoThrow) {
			const int testArray[] = { 0,2,3,4,5,6,7,8 };
			try {
				AssertArray::AllItemsAreUnique(testArray, 8);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(AllItemsAreUnique_HasCorrectVector_CheckNoThrow) {
			std::vector<int> testArray = { 0,2,3,4,5,6,7,8 };
			try {
				AssertArray::AllItemsAreUnique(testArray);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(AllItemsAreUnique_HasUncorrectVector_CheckThrow) {
			std::vector<int> testArray = { 2,2,3,4,6, 5,7,1 };
			try {
				AssertArray::AllItemsAreUnique(testArray,"TestMessage");
				Assert::Fail();
			}
			catch (AssertException ex) {
				StringAssert::Constains("TestMessage", ex.getMessage(), L"userMessage");
				StringAssert::Constains("> items are not unique", ex.getMessage(), L"assertMessage");
			}
		}
	};
}