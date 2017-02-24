#pragma once
#include <string>
#include "Exceptions.h"

namespace darknessNight {
	namespace CppUnitTestFramework {
		class AssertException :public exception {
		public:
			AssertException(std::string message) :exception(message.c_str()) {}

			std::string getMessage() {
				return std::string(what());
			}
		};

		class AssertFailException :public AssertException {
		public:
			AssertFailException(std::string message) :AssertException(message) {
			}
		};

		class AssertPassException :public AssertException {
		public:
			AssertPassException(std::string message) :AssertException(message) {
			}
		};
	}
}
