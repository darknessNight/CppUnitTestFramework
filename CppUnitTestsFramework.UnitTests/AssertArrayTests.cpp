#include "stdafx.h"
#include <CppUnitTestsFramework\AssertArray.h>
#include <vector>
#include <array>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight_CppUnitTestFramework::UnitTests {
	TEST_CLASS(AssertArrayTests)
	{
	public:
		TEST_METHOD(AreEqual_HasSameVector_CheckNoThrow){
			std::vector<int> testArray = {1,2,3,4,5,6,7,8};
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
				AssertArray::AreEqual(testArray, testArray2);
				Assert::Fail();
			}
			catch (AssertException ex) {
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
				AssertArray::AreNotEqual(testArray, testArray);
				Assert::Fail();
			}
			catch (AssertException ex) {
			}
		}

		TEST_METHOD(AreNotEqual_HasCArray_CheckThrow) {
			int testArray[] = { 1,2,3,4,5,6,7,8 };
			try {
				AssertArray::AreNotEqual(testArray,8, testArray,8);
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
			std::vector<int> testArray2 = { 4,5,6,7,8, 1,2,3};
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
				AssertArray::AreEquivalent(testArray, testArray2);
				Assert::Fail();
			}
			catch (AssertException ex) {
			}
		}

		TEST_METHOD(AreEquivalent_HasSameUnorderedCArray_CheckNoThrow) {
			int testArray[] = { 1,2,3,4,5,6,7,8 };
			int testArray2[] = { 4,5,6,7,8, 1,2,3 };
			try {
				AssertArray::AreEquivalent(testArray, 8, testArray2,8);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(AreNotEquivalent_HasSameUnorderedVector_CheckThrow) {
			std::vector<int> testArray = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray2 = { 4,5,6,7,8, 1,2,3 };
			try {
				AssertArray::AreNotEquivalent(testArray, testArray2);
				Assert::Fail();
			}
			catch (AssertException ex) {
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
				AssertArray::Contains(testArray, testArray2);
				Assert::Fail();
			}
			catch (AssertException ex) {
			}
		}

		TEST_METHOD(DoesNotConstain_HasCoinstainsVector_CheckThrow) {
			std::vector<int> testArray2 = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray = { 1,4,5,6,7,2,3 };
			try {
				AssertArray::DoesNotContain(testArray, testArray2);
				Assert::Fail();
			}
			catch (AssertException ex) {
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

		TEST_METHOD(IsSubsequence_HasCoinstainsVector_CheckNoThrow) {
			std::vector<int> testArray = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray2 = { 1,2,3,4,5,6,7 };
			try {
				AssertArray::IsSubsequence(testArray2, testArray);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}

		TEST_METHOD(IsSubsequence_HasNonCoinstainsVector_CheckThrow) {
			std::vector<int> testArray2 = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray = { 1,2,3,4,5,6,0 };
			try {
				AssertArray::IsSubsequence(testArray, testArray2);
				Assert::Fail();
			}
			catch (AssertException ex) {
			}
		}

		TEST_METHOD(IsNotSubsequence_HasCoinstainsVector_CheckThrow) {
			std::vector<int> testArray2 = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray = { 2,3,4,5,6,7, 8 };
			try {
				AssertArray::IsNotSubsequence(testArray, testArray2);
				Assert::Fail();
			}
			catch (AssertException ex) {
			}
		}

		TEST_METHOD(IsSubsequence_HasCoinstainsCArray_CheckNoThrow) {
			int testArray2[] = { 1,2,3,4,5,6,7,8 };
			int testArray[] = { 1,2,3,4,5,6,7 };
			try {
				AssertArray::IsSubsequence(testArray, 7, testArray2, 8);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}
		}



		TEST_METHOD(AreEquivalent_BigElements_CheckNoThrow) {
			/*std::vector<int> testArray = { 1,2,3,4,5,6,7,8 };
			//std::vector<int> testArray2 = { 1,2,3,4,5,6,7,8 };
			std::vector<int> testArray2 = { 4,5,6,7,8, 1,2, 3 };
			const int max = 1000000;
			for (int i = 0; i < max; i++) {
				testArray.push_back(i);
				testArray2.push_back(i);
				//testArray2.push_back(max-i-1);
			}
			//for (int i = 0; i < max; i++)
				//testArray2.push_back(i);
			
			try {
				AssertArray::Contains(testArray2, testArray);
				//AssertArray::AreEquivalent(testArray2, testArray);
			}
			catch (AssertException ex) {
				Assert::Fail();
			}*/
		}
	};
}