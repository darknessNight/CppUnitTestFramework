#pragma once
#include "BasicAssert.h"
namespace darknessNight_CppUnitTestFramework {
	class AssertExceptionCatcher : protected virtual BasicAssert {
	public:
		template <typename Exception>static Exception Throws(void(*func)(), std::string message = "");
		static void DoesNotThrow(void(*func)(), std::string message = "");
	private:
		template<typename Exception> static void throwCatchedUnexpectedException(std::exception & ex, std::string &message);
		static void throwCatchUnknowException(std::string message);
		static void throwThrowFailedMessage(std::string message);
	};

#include "AssertExceptionCatcherImplem.h"

}

