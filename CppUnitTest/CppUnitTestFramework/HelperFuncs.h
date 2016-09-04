#pragma once
#include <string>
#include <typeinfo>

namespace darknessNight {
	namespace CppUnitTestFramework {
		class ClassTypePrefix {
		private:
			static int prefixCount;
		public:
			static int strlen();
		private:
			static void setPrefixCountIfNeeded();
			static void setPrefixCount();
		};

		template <class T> std::string getClassName(T* obj) {
			return std::string(typeid(*obj).name()).substr(ClassTypePrefix::strlen());;
		}

		template <class T> std::string getClassName(T& obj) {
			return std::string(typeid(obj).name()).substr(ClassTypePrefix::strlen());
		}

		template <class T> std::string getClassName() {
			return std::string(typeid(T).name()).substr(ClassTypePrefix::strlen());
		}

		std::string extractClassName(std::string name);
	}
}
