#pragma once
#include <algorithm>
#include <regex>
#include "EqualAssert.h"

namespace darknessNight {
	namespace CppUnitTestFramework {
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
					helper.throwFailedExceptionFromPattern("Found <%expected> in <%result>", expected, result, message);
			}

			static void EndsWith(string expected, string result, string message = "") {
				if (!endsWith(expected, result))
					helper.throwFailedExceptionFromPattern("<%result> does not end with <%expected>", expected, result, message);
			}

			static void DoesNotEndWith(string expected, string result, string message = "") {
				if (endsWith(expected, result))
					helper.throwFailedExceptionFromPattern("<%result> ends with <%expected>", expected, result, message);
			}

			static void StartsWith(string expected, string result, string message = "") {
				if (!startsWith(expected, result))
					helper.throwFailedExceptionFromPattern("<%result> does not start with <%expected>", expected, result, message);
			}

			static void DoesNotStartWith(string expected, string result, string message = "") {
				if (startsWith(expected, result))
					helper.throwFailedExceptionFromPattern("<%result> starts with <%expected>", expected, result, message);
			}

			static void Match(string expected, string result, string message = "") {
				if (!match(expected, result))
					helper.throwFailedExceptionFromPattern("<%result> does not match <%expected>", expected, result, message);
			}

			static void DoesNotMatch(string expected, string result, string message = "") {
				if (match(expected, result))
					helper.throwFailedExceptionFromPattern("<%result> match <%expected>", expected, result, message);
			}


		private:
			static bool constains(string &expected, string &result) {
				return getStringPos(expected, result) >= 0;
			}

			static bool endsWith(string &expected, string &result) {
				return getStringPos(expected, result) == result.size() - expected.size();
			}

			static bool startsWith(string &expected, string &result) {
				return getStringPos(expected, result) == 0;
			}

			static int getStringPos(string& expected, string& result) {
				return result.find(expected);
			}

			static bool match(string &expected, string &result) {
				std::regex regex(expected);
				return regex_match(result, regex);
			}

			static string stringToUpper(string str) {
				transform(str.begin(), str.end(), str.begin(), toupper);
				return str;
			}

		};
	}
}