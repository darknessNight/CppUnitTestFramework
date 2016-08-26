#pragma once
#include "AssertExceptions.h"
#include "ToStringConverter.h"

namespace darknessNight_CppUnitTestFramework {
	class Assert {
	private:
		template<typename T> static std::string getAreEqualFailedMessage(const T& expected, const T& result, std::string curr) {
			if (curr.size() <= 0) {
				return "expected <" + ToStringConverter::ToString(expected) + "> but received <" + ToStringConverter::ToString(result) +">";
			}
			else {
				return curr;
			}
		}
	public:
		template<typename T> static void AreEqual(T expected, T result, std::string message="") {
			if (!(expected == result))
				throw AssertException(getAreEqualFailedMessage(expected,result, message));
		}

		template<typename T> static void AreEqual(const T* expected, const T* result, std::string message = "") {
			if (!(*expected != *result))
				throw AssertException(getAreEqualFailedMessage(expected, result, message));
		}

		static void AreEqual(const char* expected, const char* result, std::string message = "") {
			if(strcmp(expected, result)!=0)
				throw AssertException(getAreEqualFailedMessage(std::string(expected), std::string(result), message));
		}

		static void AreEqual(const wchar_t* expected, const wchar_t* result, std::string message = "") {
			if(wcscmp(expected,result)!=0)
				throw AssertException(getAreEqualFailedMessage(std::wstring(expected), std::wstring(result), message));
		}
	};
}