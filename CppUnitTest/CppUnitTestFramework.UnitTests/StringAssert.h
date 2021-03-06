#pragma once
#include <string>
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {
	namespace CppUnitTestFramework {
		class StringAssert {
		public:
			static void AreEqual(std::string expected, std::string result) {
				Assert::AreEqual(expected, result);
			}
			static void Constains(std::string expected, std::string result, std::wstring message = L"") {
				int index = result.find(expected);
				bool constainsResult = index >= 0;
				Assert::IsTrue(constainsResult, message.c_str());
			}
			static void NotConstains(std::string expected, std::string result, std::wstring message = L"") {
				int index = result.find(expected);
				bool constainsResult = index >= 0;
				Assert::IsFalse(constainsResult, message.c_str());
			}
		};

	}
}