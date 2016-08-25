#include "HelperFuncs.h"

string darknessNight::CppUnitTestFramework::extractClassName(string name) {
	return name.substr(strlen("class "));
}
