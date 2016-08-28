#pragma once
#include "AssertExceptions.h"
#include "ToStringConverter.h"
#include <cstring>

namespace darknessNight_CppUnitTestFramework {
	class BasicAssert {
	public:
		static void Fail(std::string message = "") {
			throw AssertFailException(message);
		}

		static void Pass(std::string message = "") {
			throw AssertPassException(message);
		}

		template <typename T> static void IsNull(T val, std::string message = "") {
			if (val != nullptr) {
				std::string mess = getAddOwnMessageIfExists(message, "Expected nullptr, but was <" + ToStringConverter::ToString(val) + ">");
				Fail(mess);
			}
		}

		template <typename T> static void IsNotNull(T val, std::string message = "") {
			if (val == nullptr) {
				std::string mess = getAddOwnMessageIfExists(message, "Expected non null value");
				Fail(mess);
			}
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

		static const std::string getAddOwnMessageIfExists(std::string userMessage, std::string assertMessage) {
			if (userMessage.size() <= 0)
				return assertMessage;
			else
				return assertMessage + ". Message: <" + userMessage + ">";
		}

		template <typename T> static void throwFailedExceptionFromPattern(std::string pattern, const T& expected, const T& result, std::string &message)
		{
			std::string resultStr, expectedStr;
			resultStr = ToStringConverter::ToString(result);
			expectedStr = ToStringConverter::ToString(expected);

			std::string assertMessage = getFullAssertMessage(pattern, resultStr, expectedStr, message);
			BasicAssert::Fail(assertMessage);
		}

		static std::string getFullAssertMessage(std::string pattern, std::string &result, std::string &expected, std::string &message)
		{
			replaceVars(pattern, result, expected);
			return getAddOwnMessageIfExists(message, pattern);
		}

		static void replaceVars(std::string &pattern, std::string & result, std::string & expected)
		{
			std::string resultExp = "%result", expectedExp = "%expected";
			int posResult = getStringPos(resultExp, pattern);
			int posExpected = getStringPos(expectedExp, pattern);
			if (posResult < posExpected)
				posExpected += (result.size() - resultExp.size());

			pattern = pattern.replace(posResult, resultExp.size(), result);
			pattern = pattern.replace(posExpected, expectedExp.size(), expected);
		}

		static int getStringPos(std::string& expected, std::string& result) {
			return result.find(expected);
		}
	};
}
