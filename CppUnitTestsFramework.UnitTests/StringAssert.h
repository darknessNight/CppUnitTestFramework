#pragma once
#include <string>
#include "CppUnitTest.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight::CppUnitTestFramework {
	class StringAssert
	{
	public:
		static void Constains(string expected, string result, wstring message=L"") {
			int index = result.find(expected);
			bool constainsResult = index >= 0;
			Assert::IsTrue(constainsResult,message.c_str());
		}
		static void NotConstains(string expected, string result, wstring message = L"") {
			int index = result.find(expected);
			bool constainsResult = index >= 0;
			Assert::IsFalse(constainsResult, message.c_str());
		}
	};

}