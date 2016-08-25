#pragma once
#include <string>
#include <typeinfo>


namespace darknessNight_CppUnitTestFramework {
    inline int strlen(){
		std::string name;
#ifdef _MSC_VER
		 name = "class ";
#endif 
        return name.size();
		
    }

	template <class T> std::string getClassName(T* obj) {
		return std::string(typeid(*obj).name()).substr(strlen());
	}

	template <class T> std::string getClassName(T& obj) {
		return std::string(typeid(obj).name()).substr(strlen());
	}

	template <class T> std::string getClassName() {
		return std::string(typeid(T).name()).substr(strlen());
	}

	std::string extractClassName(std::string name);
}
