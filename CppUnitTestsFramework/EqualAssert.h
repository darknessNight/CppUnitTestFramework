#pragma once
#include "BasicAssert.h"

namespace darknessNight_CppUnitTestFramework {
	class AssertEqual: protected virtual BasicAssert {
	public:
		template<typename T> static void AreEqual(T expected, T result, std::string message = "", int(*comparer)(const T&, const T&) = &BasicAssert::defaulComparer) {
			if (comparer(expected, result) != 0) throwEqualFailureMessage<T>(expected, result, message);
		}

		template<typename T> static void AreNotEqual(T expected, T result, std::string message = "", int(*comparer)(const T&, const T&) = &BasicAssert::defaulComparer) {
			if (comparer(expected, result) == 0) throwNotEqualFailureMessage<T>(expected, result, message);
		}

		template <typename T> static void AreEqualWithTolerance(T expected, T result, T tolerance, std::string message = "", int(*comparer)(const T&, const T&, const T&) = &BasicAssert::defaultComparerWithTolerance) {
			if (comparer(expected, result, tolerance) != 0) throwEqualFailureMessage<T>(expected, result, message);
		}

		template <typename T> static void AreNotEqualWithTolerance(T expected, T result, T tolerance, std::string message = "", int(*comparer)(const T&, const T&, const T&) = &BasicAssert::defaultComparerWithTolerance) {
			if (comparer(expected, result, tolerance) == 0) throwNotEqualFailureMessage<T>(expected, result, message);
		}

		template<typename T> static void AreEqualPtrValue(const T* expected, const T* result, std::string message = "", int(*comparer)(const T&, const T&) = &BasicAssert::defaulComparer) {
			if (comparer(*expected, *result) != 0) throwEqualFailureMessage<T>(*expected, *result, message);
		}

		template<typename T> static void AreNotEqualPtrValue(const T* expected, const T* result, std::string message = "", int(*comparer)(const T&, const T&) = &BasicAssert::defaulComparer) {
			if (comparer(*expected, *result) == 0) throwNotEqualFailureMessage<T>(*expected, *result, message);
		}

		template<typename T> static void AreSame(const T& expected, const T& result, std::string message = "") {
			if (defaulSameComparer(&expected, &result) != 0) throwEqualFailureMessage<T>(expected, result, message);
		}

		template<typename T> static void AreNotSame(const T& expected, const T& result, std::string message = "") {
			if (defaulSameComparer(&expected, &result) == 0) throwNotEqualFailureMessage<T>(expected, result, message);
		}

	private:
		static int defaulSameComparer(const void* expected, const void* result) {
			long long adr1 = (long long)expected;
			long long adr2 = (long long)result;
			return BasicAssert::defaulComparer(adr1, adr2);
		}

		template<typename T> static void throwNotEqualFailureMessage(const T &expected, const T &result, std::string &message) {
			throwFailedExceptionFromPattern("Objects are equal. expected <%expected>, but has <%result>", expected, result, message);
		}

		template<typename T> static void throwEqualFailureMessage(const T &expected, const T &result, std::string &message) {
			throwFailedExceptionFromPattern("Objects are difference. expected <%expected>, but has <%result>", expected, result, message);
		}
	};
}