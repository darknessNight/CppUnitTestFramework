#pragma once
#include "EqualAssert.h"
#include <algorithm>

namespace darknessNight_CppUnitTestFramework {
	using std::string;
	class AssertString :protected virtual BasicAssert {
	public:
		static void AreEqual(string expected, string result, string message = "") {
			AssertEqual::AreEqual(expected, result, message);
		}

		static void AreNotEqual(string expected, string result, string message = "") {
			AssertEqual::AreNotEqual(expected, result, message);
		}

		static void AreEqualIgnoringCase(string expected, string result, string message = "") {
			expected = stringToUpper(expected);
			result = stringToUpper(result);
			AreEqual(expected, result, message);
		}

		static void AreNotEqualIgnoringCase(string expected, string result, string message = "") {
			expected = stringToUpper(expected);
			result = stringToUpper(result);
			AreNotEqual(expected, result, message);
		}

		static void Contains(string expected, string result, string message = "") {
			if (!constains(expected, result)) 
				helper.throwFailedExceptionFromPattern("Not found <%expected> in <%result>", expected, result, message);
		}

		static void NotContains(string expected, string result, string message = "") {
			if (constains(expected, result)) 
				helper.throwFailedExceptionFromPattern("Found <%expected> in <%result>", expected,result,  message);
		}

		static void EndsWith(string expected, string result, string message = "") {
			if (!endsWith(expected, result)) 
				helper.throwFailedExceptionFromPattern("<%result> does not end with <%expected>", expected,result,  message);
		}

		static void DoesNotEndWith(string expected, string result, string message = "") {
			if (endsWith(expected, result)) 
				helper.throwFailedExceptionFromPattern("<%result> ends with <%expected>", expected,result,  message);
		}

		static void StartsWith(string expected, string result, string message = "") {
			if (!startsWith(expected, result)) 
				helper.throwFailedExceptionFromPattern("<%result> does not start with <%expected>", expected,result,  message);
		}

		static void DoesNotStartWith(string expected, string result, string message = "") {
			if (startsWith(expected, result))
				helper.throwFailedExceptionFromPattern("<%result> starts with <%expected>", expected,result,  message);
		}

		static void StartsWith(string expected, string result, string message = "") {
			if (!match(expected, result))
				helper.throwFailedExceptionFromPattern("<%result> does not match <%expected>", expected, result, message);
		}

		static void DoesNotStartWith(string expected, string result, string message = "") {
			if (match(expected, result))
				helper.throwFailedExceptionFromPattern("<%result> match <%expected>", expected, result, message);
		}


	private:
		static bool constains(std::string &expected, std::string &result)
		{
			return getStringPos(expected, result) >= 0;
		}

		static bool endsWith(std::string &expected, std::string &result)
		{
			return getStringPos(expected, result) == result.size() - expected.size();
		}

		static bool startsWith(std::string &expected, std::string &result)
		{
			return getStringPos(expected, result) == 0;
		}

		static int getStringPos(std::string& expected, std::string& result) {
			return result.find(expected);
		}

		static string stringToUpper(string str) {
			std::transform(str.begin(), str.end(), str.begin(), ::toupper);
			return str;
		}

	};
}