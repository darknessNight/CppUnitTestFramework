#pragma once
#include <string>
#include "BasicAssert.h"

namespace darknessNight {
	namespace CppUnitTestFramework {
		class AssertHelper {
		private:
			std::string resultExp = "%result";
			std::string expectedExp = "%expected";
		public:
			template <typename T> void throwFailedExceptionFromPattern(std::string pattern, const T& expected, const T& result, std::string &message);
			const std::string getAddOwnMessageIfExists(std::string userMessage, std::string assertMessage);
		private:
			std::string getFullAssertMessage(std::string pattern, const std::string &expected, const std::string &result, std::string &message);
			std::string replaceVars(std::string &pattern, const std::string & expected, const std::string & result);
			int getResultVarPos(std::string & pattern);
			int getExpectedVarPos(std::string & pattern, int posResult, const std::string & result);
			std::string replaceVarOnPos(std::string & pattern, int posResult, int repLenght, const std::string & result);
			int getStringPos(std::string& expected, std::string& result);
		};

		template<typename T>
		inline void AssertHelper::throwFailedExceptionFromPattern(std::string pattern, const T & expected, const T & result, std::string & message) {
			std::string resultStr, expectedStr;
			resultStr = ToStringConverter::ToString(result);
			expectedStr = ToStringConverter::ToString(expected);

			std::string assertMessage = getFullAssertMessage(pattern, expectedStr, resultStr, message);
			BasicAssert::Fail(assertMessage);
		}

		template<>
		inline void AssertHelper::throwFailedExceptionFromPattern(std::string pattern, const std::string & expected, const std::string & result, std::string & message) {
			std::string assertMessage = getFullAssertMessage(pattern, expected, result, message);
			BasicAssert::Fail(assertMessage);
		}
	}
}