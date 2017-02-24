#pragma once
#include <iterator>
#include <vector>
#include <map>
#include "EqualAssert.h"

using namespace std;

namespace darknessNight {
	namespace CppUnitTestFramework {
		class AssertArray :protected virtual BasicAssert {
		public:
			template <typename T> static void AreEqual(T &expected, T &result, string message = "") {
				if (!checkAreEqual(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
					helper.throwFailedExceptionFromPattern("Expected <%expected>, but was <%result>", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
			}

			template <typename T> static void AreEqual(const T *expected, unsigned expLen, const T *result, unsigned resLen, string message = "") {
				if (!checkAreEqual(expected, &expected[expLen], result, &result[resLen]))
					helper.throwFailedExceptionFromPattern("Expected <%expected>, but was <%result>", ToStringConverter::ArrayToString(expected, expLen), ToStringConverter::ArrayToString(result, resLen), message);
			}

			template <typename T> static void AreNotEqual(T &expected, T &result, string message = "") {
				if (checkAreEqual(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
					helper.throwFailedExceptionFromPattern("Arrays are equal", string(), string(), message);
			}

			template <typename T> static void AreNotEqual(const T *expected, unsigned expLen, const T *result, unsigned resLen, string message = "") {
				if (checkAreEqual(expected, &expected[expLen], result, &result[resLen]))
					helper.throwFailedExceptionFromPattern("Arrays are equal", string(), string(), message);
			}

			template <typename T> static void AreEquivalent(T &expected, T &result, string message = "") {
				if (!checkAreEquivalent(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
					helper.throwFailedExceptionFromPattern("Expected <%expected>, but was <%result>", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
			}

			template <typename T> static void AreEquivalent(const T *expected, unsigned expLen, const T *result, unsigned resLen, string message = "") {
				if (!checkAreEquivalent(expected, &expected[expLen], result, &result[resLen]))
					helper.throwFailedExceptionFromPattern("Expected <%expected>, but was <%result>", ToStringConverter::ArrayToString(expected, expLen), ToStringConverter::ArrayToString(result, resLen), message);
			}

			template <typename T> static void AreNotEquivalent(T &expected, T &result, string message = "") {
				if (checkAreEquivalent(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
					helper.throwFailedExceptionFromPattern("Arrays are equivalents", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
			}

			template <typename T> static void AreNotEquivalent(const T *expected, unsigned expLen, const T *result, unsigned resLen, string message = "") {
				if (checkAreEquivalent(expected, &expected[expLen], result, &result[resLen]))
					helper.throwFailedExceptionFromPattern("Arrays are equivalents", ToStringConverter::ArrayToString(expected, expLen), ToStringConverter::ArrayToString(result, resLen), message);
			}

			template <typename T> static void Contains(T &expected, T &result, string message = "") {
				if (!checkContains(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
					helper.throwFailedExceptionFromPattern("Expected constains <%expected>, but was <%result>", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
			}

			template <typename T> static void Contains(const T *expected, unsigned expLen, const T *result, unsigned resLen, string message = "") {
				if (!checkContains(expected, &expected[expLen], result, &result[resLen]))
					helper.throwFailedExceptionFromPattern("Expected constains <%expected>, but was <%result>", ToStringConverter::ArrayToString(expected, expLen), ToStringConverter::ArrayToString(result, resLen), message);
			}

			template <typename T> static void DoesNotContain(T &expected, T &result, string message = "") {
				if (checkContains(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
					helper.throwFailedExceptionFromPattern("Result array constains expected array", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
			}

			template <typename T> static void DoesNotContain(const T *expected, unsigned expLen, const T *result, unsigned resLen, string message = "") {
				if (checkContains(expected, &expected[expLen], result, &result[resLen]))
					helper.throwFailedExceptionFromPattern("Result array constains expected array", ToStringConverter::ArrayToString(expected, expLen), ToStringConverter::ArrayToString(result, resLen), message);
			}

			template <typename T> static void IsSubsequence(T &expected, T &result, string message = "") {
				if (!checkIsSubsequence(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
					helper.throwFailedExceptionFromPattern("<%result> has not subsequence <%expected>", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
			}

			template <typename T> static void IsSubsequence(const T *expected, unsigned expLen, const T *result, unsigned resLen, string message = "") {
				if (!checkIsSubsequence(expected, &expected[expLen], result, &result[resLen]))
					helper.throwFailedExceptionFromPattern("<%result> has not subsequence <%expected>", ToStringConverter::ArrayToString(expected, expLen), ToStringConverter::ArrayToString(result, resLen), message);
			}

			template <typename T> static void IsNotSubsequence(T &expected, T &result, string message = "") {
				if (checkIsSubsequence(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
					helper.throwFailedExceptionFromPattern("<%result> has subsequence <%expected>", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
			}

			template <typename T> static void IsNotSubsequence(const T *expected, unsigned expLen, const T *result, unsigned resLen, string message = "") {
				if (checkIsSubsequence(expected, &expected[expLen], result, &result[resLen]))
					helper.throwFailedExceptionFromPattern("<%result> has subsequence <%expected>", ToStringConverter::ArrayToString(expected, expLen), ToStringConverter::ArrayToString(result, resLen), message);
			}

			template <typename T> static void IsOrdered(T &result, string message = "") {
				if (!checkIsOrdered(std::begin(result), std::end(result)))
					helper.throwFailedExceptionFromPattern("Array <%result> is not ordered", string(), ToStringConverter::ArrayToString(result), message);
			}

			template <typename T> static void IsOrdered(const T *result, unsigned resLen, string message = "") {
				if (!checkIsOrdered(result, &result[resLen]))
					helper.throwFailedExceptionFromPattern("Array <%result> is not ordered", string(), ToStringConverter::ArrayToString(result, resLen), message);
			}

			template <typename T> static void IsNotOrdered(T &result, string message = "") {
				if (checkIsOrdered(std::begin(result), std::end(result)))
					helper.throwFailedExceptionFromPattern("Array <%result> is ordered", string(), ToStringConverter::ArrayToString(result), message);
			}

			template <typename T> static void IsNotOrdered(const T *result, unsigned resLen, string message = "") {
				if (checkIsOrdered(result, &result[resLen]))
					helper.throwFailedExceptionFromPattern("Array <%result> is ordered", string(), ToStringConverter::ArrayToString(result, resLen), message);
			}

			template <class T> static void AllItemsAre(T &result, bool(*predicate)(typename T::const_iterator), string message = "") {
				if (!checkAllItemsAre(std::begin(result), std::end(result), predicate))
					helper.throwFailedExceptionFromPattern("Array <%result> items not satisfy a predicate", string(), ToStringConverter::ArrayToString(result), message);
			}

			template <typename T> static void AllItemsAre(const T *result, unsigned resLen, bool(*predicate)(const T*), string message = "") {
				if (!checkAllItemsAre(result, &result[resLen], predicate))
					helper.throwFailedExceptionFromPattern("Array <%result> items not satisfy a predicate", string(), ToStringConverter::ArrayToString(result, resLen), message);
			}

			template <class T> static void AllItemsAreUnique(T &result, string message = "") {
				if (!checkAllItemsAreUnique(std::begin(result), std::end(result)))
					helper.throwFailedExceptionFromPattern("Array <%result> items are not unique", string(), ToStringConverter::ArrayToString(result), message);
			}

			template <typename T> static void AllItemsAreUnique(const T *result, unsigned resLen, string message = "") {
				if (!checkAllItemsAreUnique(result, &result[resLen]))
					helper.throwFailedExceptionFromPattern("Array <%result> items are not unique", string(), ToStringConverter::ArrayToString(result, resLen), message);
			}

		private:
			template<typename T> static bool checkAreEqual(T expIter, T expEnd, T resIter, T resEnd);
			template<typename T> static bool isDiffLenght(T& expIter, T& expEnd, T& resIter, T& resEnd);
			template<typename T> static bool checkAreEquivalent(T expIter, T expEnd, T resIter, T resEnd);
			template<typename T> static void sortArrays(std::vector<T> &resEls, std::vector<T> &expEls);
			template<typename T, typename U> static std::vector<T> getCopyOfArray(U& arrIter, U& arrEnd);
			template<typename T> static bool checkContains(T expIter, T expEnd, T resIter, T resEnd);
			template<typename T> static bool findAllElements(std::vector<T> &expEls, std::vector<T> &resEls);
			template<typename T, typename U, typename W>
			static bool hasPassElementInResult(W &res, std::vector<T> & resEls, U &exp);
			template<typename T> static bool checkIsSubsequence(T expIter, T expEnd, T resIter, T resEnd);
			template<typename T> static bool findSubsequence(T &resIter, T &resEnd, T &expIter, T &expEnd);
			template<typename T> static bool isSubsequence(T & resIter, T & expIter, T & resEnd, T & expEnd);
			template<typename T> static void moveIteratorToEndEqualSequences(T &resI, T &expI, T & resEnd, T & expEnd);
			template<typename T> static bool foundedSubsequence(T &expI, T & expEnd, T &resI, T & resEnd);
			template<typename T> static bool checkIsOrdered(T resIter, T resEnd);
			template<typename T> static bool checkOrderedAllItems(T &resIter, T &resEnd, T &oldVal);
			template<typename T, typename U> static bool checkAllItemsAre(T resIter, T resEnd, bool(*predicate)(const U item));
			template<typename T> static bool checkAllItemsAreUnique(T resIter, T resEnd);
			template<typename T> static bool checkAllItemsOccurrOnlyOnce(std::map<T, int> &els);
			template<typename U, typename T> static std::map<U, int> countOccurrences(T &resIter, T &resEnd);
		};
#include "AssertArrayImplem.h"
	}
}