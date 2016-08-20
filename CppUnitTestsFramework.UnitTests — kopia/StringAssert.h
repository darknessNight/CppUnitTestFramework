#pragma once
#include <string>
#include "CppUnitTest.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight::CppUnitTestFramework {
	class StringAssert
	{
	public:
		static void Constains(string expected, string result) {
			int index = result.find(expected);
			bool constainsResult = index >= 0;
			Assert::IsTrue(constainsResult);
		}
		static void NotConstains(string expected, string result) {
			int index = result.find(expected);
			bool constainsResult = index >= 0;
			Assert::IsFalse(constainsResult);
		}
	};

}