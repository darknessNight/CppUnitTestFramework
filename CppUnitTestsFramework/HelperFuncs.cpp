#include "HelperFuncs.h"

std::string darknessNight_CppUnitTestFramework::extractClassName(std::string name) {
	return name.substr(ClassTypePrefix::strlen());
}

int darknessNight_CppUnitTestFramework::ClassTypePrefix::prefixCount = -1;

int darknessNight_CppUnitTestFramework::ClassTypePrefix::strlen() {
	setPrefixCountIfNeeded();
	return prefixCount;
}

void darknessNight_CppUnitTestFramework::ClassTypePrefix::setPrefixCountIfNeeded() {
	if (prefixCount < 0) {
		setPrefixCount();
	}
}


#ifdef _MSC_VER
class HelperClass {};

void darknessNight_CppUnitTestFramework::ClassTypePrefix::setPrefixCount()
{
	std::string name = typeid(HelperClass).name();
	prefixCount = name.find("HelperClass");
}
#else
void darknessNight_CppUnitTestFramework::ClassTypePrefix::setPrefixCount() {
	prefixCount = 0;
}
#endif
