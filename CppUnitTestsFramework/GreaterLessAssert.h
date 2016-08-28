#pragma once
#include "BasicAssert.h"

namespace darknessNight_CppUnitTestFramework {
	class AssertGreaterLess : protected virtual BasicAssert {
	public:
		template <typename T> static void Greater(T expected, T result, std::string message = "", int(*comparer)(const T&, const T&) = &BasicAssert::defaulComparer) {
			if (comparer(expected, result) >= 0) 
				throwGreaterFailureMessage<T>(expected, result, message);
		}

		template <typename T> static void GreaterEqual(T expected, T result, std::string message = "", int(*comparer)(const T&, const T&) = &BasicAssert::defaulComparer) {
			if (comparer(expected, result) > 0)
				throwGreaterFailureMessage<T>(expected, result, message);
		}

		template <typename T> static void LessEqual(T expected, T result, std::string message = "", int(*comparer)(const T&, const T&) = &BasicAssert::defaulComparer) {
			if (comparer(expected, result) < 0)
				throwLessFailureMessage<T>(expected, result, message);
		}

		template <typename T> static void Less(T expected, T result, std::string message = "", int(*comparer)(const T&, const T&) = &BasicAssert::defaulComparer) {
			if (comparer(expected, result) <= 0)
				throwLessFailureMessage<T>(expected, result, message);
		}

	private:
		template<typename T> static void throwLessFailureMessage(const T &expected, const T &result, std::string &message) {
			throwFailedExceptionFromPattern<T>("Result is to big. Expected <%expected>, but was <%result>", expected, result, message);
		}

		template<typename T> static void throwGreaterFailureMessage(const T &expected, const T &result, std::string &message) {
			throwFailedExceptionFromPattern<T>("Result is to small. Expected <%expected>, but was <%result>", expected, result, message);
		}
	};
}