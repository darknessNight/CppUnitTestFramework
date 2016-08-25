#pragma once
#include <string>
using namespace std;

namespace darknessNight::CppUnitTestFramework {
	template <class T> string getClassName(T* obj) {
		return string(typeid(*obj).name()).substr(strlen("class "));
	}

	template <class T> string getClassName(T& obj) {
		return string(typeid(obj).name()).substr(strlen("class "));
	}

	template <class T> string getClassName() {
		return string(typeid(T).name()).substr(strlen("class "));
	}

	string extractClassName(string name);
}