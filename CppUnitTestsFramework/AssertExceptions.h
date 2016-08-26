#pragma once
#include "Exceptions.h"
#include <string>
namespace darknessNight_CppUnitTestFramework {
	class AssertException :public exception {
	public:
		AssertException(const char* message) :exception(message) {
		}

		AssertException(std::string message) :exception(message.c_str()) {
		}

		std::string getMessage() {
			return std::string(what());
		}
	};
}
