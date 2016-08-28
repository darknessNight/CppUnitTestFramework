#pragma once
#include "AssertExceptions.h"
#include "ToStringConverter.h"
#include <cstring>

namespace darknessNight_CppUnitTestFramework {
	class AssertHelper;

	class BasicAssert {
	protected:
		static AssertHelper helper;
	public:
		static void Fail(std::string message = "");
		static void Pass(std::string message = "");
		template <typename T> static void IsNull(T val, std::string message = "");
		template <typename T> static void IsNotNull(T val, std::string message = "");

	protected:
		template <typename T> static int defaultComparerWithTolerance(T expected, T result, T tolerance);
		template<typename T> static int defaulComparer(const T& expected, const T& result);
		static int defaulComparer(const char* expected, const char* result);
		static int defaulComparer(const wchar_t* expected, const wchar_t* result, std::string message = "");
	};

#include "BasicAssertImplem.h"
}
#include "AssertHelper.h"
