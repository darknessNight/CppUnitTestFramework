#pragma once
#include "AssertExceptions.h"
#include "ToStringConverter.h"

namespace darknessNight_CppUnitTestFramework {
	class Assert {
	public:
		template<typename T> static void AreEqual(T expected, T result, std::string message = "") {
			if (!compare(expected, result)) throwEqualFailureMessage<T>(expected, result, message);
		}

		template<typename T> static void AreNotEqual(T expected, T result, std::string message = "") {
			if (compare(expected, result)) throwNotEqualFailureMessage(message);
		}

		template <typename T> static void AreEqual(T expected, T result, T tolerance, std::string message = "") {
			if (!compareWithTolerance(expected, result, tolerance)) throwEqualFailureMessage<T>(expected, result, message);
		}

		template <typename T> static void AreNotEqual(T expected, T result, T tolerance, std::string message = "") {
			if (compareWithTolerance(expected, result, tolerance)) throwNotEqualFailureMessage(message);
		}

		template<typename T> static void AreEqualPtrValue(const T* expected, const T* result, std::string message = "") {
			if (!compare(*expected, *result)) throwEqualFailureMessage<T>(*expected, *result, message);
		}

		template<typename T> static void AreNotEqualPtrValue(const T* expected, const T* result, std::string message = "") {
			if (compare(*expected, *result)) throwNotEqualFailureMessage(message);
		}

	private:
		template<typename T> static void throwEqualFailureMessage(const T &expected, const T &result, std::string &message) {
			throw AssertException(getAreEqualFailedMessage(expected, result, message));
		}

		static void throwNotEqualFailureMessage(std::string &message){
			std::string mess = getAddOwnMessageIfExists(message, "Object is same");
			throw AssertException(mess);
		}
		template <typename T> static bool compareWithTolerance(T expected, T result, T tolerance) {
			return expected - tolerance<result && expected + tolerance>result;
		}

		template<typename T> static bool compare(T& expected, T& result) {
			return (expected == result);
		}

		static bool compare(const char* expected, const char* result) {
			return (strcmp(expected, result) == 0);
		}

		static bool compare(const wchar_t* expected, const wchar_t* result, std::string message = "") {
			return(wcscmp(expected, result) == 0);
		}
		template<typename T> static std::string getAreEqualFailedMessage(const T& expected, const T& result, std::string userMessage) {
			std::string notEqualMess = getCompareErrorMessage(expected, result);
			return getAddOwnMessageIfExists(userMessage, notEqualMess);
		}

		static const std::string getAddOwnMessageIfExists(std::string userMessage, std::string notEqualMess) {
			if (userMessage.size() <= 0) {
				return notEqualMess;
			}
			else {
				return notEqualMess + ". Message: <" + userMessage + ">";
			}
		}

		template<typename T> static const std::string getCompareErrorMessage(const T& expected, const T& result) {
			return "expected <" + ToStringConverter::ToString(expected) + "> but received <" + ToStringConverter::ToString(result) + ">";
		}
	};
}