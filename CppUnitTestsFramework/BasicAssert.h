#pragma once
#include "AssertExceptions.h"
#include "ToStringConverter.h"

namespace darknessNight_CppUnitTestFramework {
	class BasicAssert {
	public:
		static void Fail(std::string message) {
			throw AssertFailException(message);
		}

		static void Pass(std::string message) {
			throw AssertPassException(message);
		}

		template <typename T> static void IsNull(T val) {
			if (val != nullptr)
				Fail("Expected nullptr, but was <"+ToStringConverter::ToString(val)+">");
		}

		template <typename T> static void IsNotNull(T val) {
			if (val == nullptr)
				Fail("Expected non null value");
		}

	protected:
		template <typename T> static int defaultComparerWithTolerance(T expected, T result, T tolerance) {
			if (expected + tolerance < result)
				return -1;
			else if (expected - tolerance > result)
				return 1;
			else return 0;

		}

		template<typename T> static int defaulComparer(const T& expected, const T& result) {
			if (expected < result)
				return -1;
			else if (expected == result)
				return 0;
			else return 1;
		}

		static int defaulComparer(const char* expected, const char* result) {
			return (strcmp(expected, result));
		}

		static int defaulComparer(const wchar_t* expected, const wchar_t* result, std::string message = "") {
			return(wcscmp(expected, result));
		}

		template<typename T> static std::string getFailureMessageString(const T& expected, const T& result, std::string userMessage) {
			std::string notEqualMess = getCompareErrorMessage(expected, result);
			return getAddOwnMessageIfExists(userMessage, notEqualMess);
		}

		static const std::string getAddOwnMessageIfExists(std::string userMessage, std::string notEqualMess) {
			if (userMessage.size() <= 0)
				return notEqualMess;
			else
				return notEqualMess + ". Message: <" + userMessage + ">";
		}

		template<typename T> static const std::string getCompareErrorMessage(const T& expected, const T& result) {
			return "expected <" + ToStringConverter::ToString(expected) + "> but received <" + ToStringConverter::ToString(result) + ">";
		}
	};
}