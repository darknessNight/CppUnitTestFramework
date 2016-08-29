#pragma once
#include "EqualAssert.h"
#include <iterator>
#include <vector>

namespace darknessNight_CppUnitTestFramework {
	class AssertArray:protected virtual BasicAssert {
	public:
		template <typename T> static void AreEqual(T &expected, T &result, std::string message="") {
			if(!checkAreEqual(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
				BasicAssert::helper.throwFailedExceptionFromPattern("Expected <%expected>, but was <%result>", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
		}

		template <typename T> static void AreEqual(const T *expected, unsigned expLen, const T *result, unsigned resLen, std::string message = "") {
			if(!checkAreEqual(expected, &expected[expLen], result, &result[resLen]))
				BasicAssert::helper.throwFailedExceptionFromPattern("Expected <%expected>, but was <%result>", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
		}

		template <typename T> static void AreNotEqual(T &expected, T &result, std::string message = "") {
			if (checkAreEqual(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
				BasicAssert::Fail("Arrays are equal");
		}

		template <typename T> static void AreNotEqual(const T *expected, unsigned expLen, const T *result, unsigned resLen, std::string message = "") {
			if (checkAreEqual(expected, &expected[expLen], result, &result[resLen]))
				BasicAssert::Fail("Arrays are equal");
		}

		template <typename T> static void AreEquivalent(T &expected, T &result, std::string message = "") {
			if (!checkAreEquivalent(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
				BasicAssert::helper.throwFailedExceptionFromPattern("Expected <%expected>, but was <%result>", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
		}

		template <typename T> static void AreEquivalent(const T *expected, unsigned expLen, const T *result, unsigned resLen, std::string message = "") {
			if (!checkAreEquivalent(expected, &expected[expLen], result, &result[resLen]))
				BasicAssert::helper.throwFailedExceptionFromPattern("Expected <%expected>, but was <%result>", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
		}

		template <typename T> static void AreNotEquivalent(T &expected, T &result, std::string message = "") {
			if (checkAreEquivalent(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
				BasicAssert::helper.throwFailedExceptionFromPattern("Arrays are equivalents", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
		}

		template <typename T> static void AreNotEquivalent(const T *expected, unsigned expLen, const T *result, unsigned resLen, std::string message = "") {
			if (checkAreEquivalent(expected, &expected[expLen], result, &result[resLen]))
				BasicAssert::helper.throwFailedExceptionFromPattern("Arrays are equivalents", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
		}

		template <typename T> static void Contains(T &expected, T &result, std::string message = "") {
			if (!checkContains(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
				BasicAssert::helper.throwFailedExceptionFromPattern("Expected <%expected>, but was <%result>", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
		}

		template <typename T> static void Contains(const T *expected, unsigned expLen, const T *result, unsigned resLen, std::string message = "") {
			if (!checkContains(expected, &expected[expLen], result, &result[resLen]))
				BasicAssert::helper.throwFailedExceptionFromPattern("Expected <%expected>, but was <%result>", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
		}

		template <typename T> static void DoesNotContain(T &expected, T &result, std::string message = "") {
			if (checkContains(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
				BasicAssert::helper.throwFailedExceptionFromPattern("Expected array constains result array", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
		}

		template <typename T> static void DoesNotContain(const T *expected, unsigned expLen, const T *result, unsigned resLen, std::string message = "") {
			if (checkContains(expected, &expected[expLen], result, &result[resLen]))
				BasicAssert::helper.throwFailedExceptionFromPattern("Expected array constains result array", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
		}

		template <typename T> static void IsSubsequence(T &expected, T &result, std::string message = "") {
			if (!checkIsSubsequence(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
				BasicAssert::helper.throwFailedExceptionFromPattern("Expected <%expected>, but was <%result>", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
		}

		template <typename T> static void IsSubsequence(const T *expected, unsigned expLen, const T *result, unsigned resLen, std::string message = "") {
			if (!checkIsSubsequence(expected, &expected[expLen], result, &result[resLen]))
				BasicAssert::helper.throwFailedExceptionFromPattern("Expected <%expected>, but was <%result>", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
		}

		template <typename T> static void IsNotSubsequence(T &expected, T &result, std::string message = "") {
			if (checkIsSubsequence(std::begin(expected), std::end(expected), std::begin(result), std::end(result)))
				BasicAssert::helper.throwFailedExceptionFromPattern("Expected array constains result array", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
		}

		template <typename T> static void IsNotSubsequence(const T *expected, unsigned expLen, const T *result, unsigned resLen, std::string message = "") {
			if (checkIsSubsequence(expected, &expected[expLen], result, &result[resLen]))
				BasicAssert::helper.throwFailedExceptionFromPattern("Expected array constains result array", ToStringConverter::ArrayToString(expected), ToStringConverter::ArrayToString(result), message);
		}
		
	private:
		template<typename T>
		static bool checkAreEqual(T expIter, T expEnd, T resIter, T resEnd)
		{
			if (isDiffLenght(expIter,expEnd,resIter,resEnd))
				return false;

			return std::equal(expIter, expEnd, resIter, resEnd);
		}

		template<typename T>
		static bool isDiffLenght(T& expIter, T& expEnd, T& resIter, T& resEnd) {
			return expEnd - expIter != resEnd - resIter;
		}

		template<typename T>
		static bool checkAreEquivalent(T expIter, T expEnd, T resIter, T resEnd)
		{
			if (isDiffLenght(expIter, expEnd, resIter, resEnd))
				return false;

			auto el = *expIter;
			auto resEls = getCopyOfArray<decltype(el)>(resIter, resEnd);
			auto expEls = getCopyOfArray<decltype(el)>(expIter, expEnd);
			sortArrays(resEls, expEls);
			return checkAreEqual(resEls.begin(), resEls.end(), expEls.begin(), expEls.end());
		}

		template<typename T>
		static void sortArrays(std::vector<T> &resEls, std::vector<T> &expEls)
		{
			std::sort(resEls.begin(), resEls.end());
			std::sort(expEls.begin(), expEls.end());
		}

		template<typename T, typename U> static std::vector<T> getCopyOfArray(U& arrIter, U& arrEnd) {
			std::vector<T> arrEls(arrEnd - arrIter);
			std::copy(arrIter, arrEnd, arrEls.begin());
			return arrEls;
		}

		template<typename T>
		static bool checkContains(T expIter, T expEnd, T resIter, T resEnd)
		{
			if (resEnd - resIter < expEnd - expIter)
				return false;

			auto el = *expIter;
			auto resEls = getCopyOfArray<decltype(el)>(resIter, resEnd);
			auto expEls = getCopyOfArray<decltype(el)>(expIter, expEnd);
			std::sort(resEls.begin(), resEls.end());

			return findAllElements(expIter, expEnd, resEls);
		}

		template<typename T, typename U>
		static bool findAllElements(T &expIter, T &expEnd, std::vector<U> &resEls)
		{
			for (; expIter != expEnd; expIter++) {
				if (!std::binary_search(resEls.begin(), resEls.end(), *expIter))
					return false;
			}
			return true;
		}

		template<typename T>
		static bool checkIsSubsequence(T expIter, T expEnd, T resIter, T resEnd)
		{
			if (resEnd - resIter < expEnd - expIter || expEnd - expIter<=0)
				return false;

			for (; resIter != resEnd; resIter++) {
				
			}
			return false;
		}
	};
}