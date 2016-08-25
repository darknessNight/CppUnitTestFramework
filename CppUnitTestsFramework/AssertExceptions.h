#pragma once
#include <string>
namespace darknessNight_CppUnitTestFramework {
	class AssertException :public exception {
	public:
		AssertException(const char* message) :exception(message) {
		}

		AssertException(std::string message) :exception(message.c_str()) {
		}
	};
}
