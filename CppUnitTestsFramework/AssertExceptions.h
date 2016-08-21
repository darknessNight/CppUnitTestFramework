#pragma once
#include <string>
namespace darknessNight::CppUnitTestFramework {
	class AssertException :public std::exception {
	public:
		AssertException(const char* message) :exception(message) {
		}

		AssertException(std::string message) :exception(message.c_str()) {
		}
	};
}
