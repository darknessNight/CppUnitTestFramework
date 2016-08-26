#pragma once
#include <typeinfo>
#include <string>

namespace darknessNight_CppUnitTestFramework {
	class ToStringConverter {
	public:
		template <typename T> static std::string ToString(const T& obj) {
			return typeid(obj).name();
		}

		static std::string ToString(const int& obj) {
			return std::to_string(obj);
		}

		static std::string ToString(const std::string& obj) {
			return "\""+obj+"\"";
		}
	};
}