#include "stdafx.h"
#include <CppUnitTestsFramework\ToStringConverter.h>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight_CppUnitTestFramework::UnitTests {
	class ToStringableClass {
	public:
		static std::string ToString(const ToStringableClass obj) {
			return "StringableClass is string";
		}

		std::string ToString() {
			return ToString(*this);
		}
	};
	TEST_CLASS(ToStringConverterTests)
	{
	public:
		TEST_METHOD(ToString_HasBasicTypes_CheckIsConvertedToString)
		{
			const int two = 2;
			assertToStringConvert(two, "2");
			assertToStringConvert(2, "2");
			assertToStringConvert(-2, "-2");
			assertToStringConvertNonEqual(2.0, "2.0");
			assertToStringConvertNonEqual(-2.0, "-2.0");
			assertToStringConvertNonEqual(2.0f, "2.0");
			assertToStringConvert(2U, "2");
			assertToStringConvert("2", "\"2\"");
			assertToStringConvert(std::string("2"), "\"2\"");
			const std::string str = "2";
			assertToStringConvert(str, "\"2\"");
		}

		template <typename T> void assertToStringConvert(T obj, std::string string) {
			StringAssert::AreEqual(string, ToStringConverter::ToString(obj));
		}

		template <typename T> void assertToStringConvertNonEqual(T obj, std::string string) {
			StringAssert::Constains(string, ToStringConverter::ToString(obj));
		}

		TEST_METHOD(RegisterConvertFunc_HasToStringMethod_CheckCorrectRegister) {
			ToStringableClass obj;
			ToStringConverter::RegisterConventerFunction<ToStringableClass>(&ToStringableClass::ToString);
			std::string result = ToStringConverter::ToString(obj);
			StringAssert::AreEqual(obj.ToString(), result);
		}

		TEST_METHOD(ToString_HasWString_CheckCorrectConvert) {
			std::string result = ToStringConverter::ToString(std::wstring(L"Ana³"));
			StringAssert::Constains("Ana", result);
		}

		TEST_METHOD(ArrayToString_HasVector_CheckCorrectConvert) {
			std::vector<int> testArray = { 1,2,3,4 };
			std::string result = ToStringConverter::ArrayToString(testArray);
			StringAssert::Constains("1, 2, 3, 4", result);
		}

		TEST_METHOD(ArrayToString_HasCArray_CheckCorrectConvert) {
			int testArray[] = { 1,2,3,4 };
			std::string result = ToStringConverter::ArrayToString(testArray,4);
			StringAssert::Constains("1, 2, 3, 4", result);
		}
	};
}