#pragma once
#include "EqualAssert.h"

namespace darknessNight {
	namespace CppUnitTestFramework {
		class AssertBoolean {
		public:
			void isTrue(bool condition, std::string message = "") {
				AssertEqual::AreEqual(true, condition, message);
			}

			void isFalse(bool condition, std::string message = "") {
				AssertEqual::AreEqual(false, condition, message);
			}
		};
	}
}