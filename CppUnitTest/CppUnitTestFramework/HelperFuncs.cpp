#include "HelperFuncs.h"

std::string darknessNight::CppUnitTestFramework::extractClassName(std::string name) {
	return name.substr(ClassTypePrefix::strlen());
}

int darknessNight::CppUnitTestFramework::ClassTypePrefix::prefixCount = -1;

int darknessNight::CppUnitTestFramework::ClassTypePrefix::strlen() {
	setPrefixCountIfNeeded();
	return prefixCount;
}

void darknessNight::CppUnitTestFramework::ClassTypePrefix::setPrefixCountIfNeeded() {
	if (prefixCount < 0) {
		setPrefixCount();
	}
}


#if _MSC_VER
class HelperClass {};

void darknessNight::CppUnitTestFramework::ClassTypePrefix::setPrefixCount()
{
	std::string name = typeid(HelperClass).name();
	prefixCount = name.find("HelperClass");
}
#else
void darknessNight::CppUnitTestFramework::ClassTypePrefix::setPrefixCount() {
	prefixCount = 0;
}
#endif
