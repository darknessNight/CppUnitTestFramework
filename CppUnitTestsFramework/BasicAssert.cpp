#include "BasicAssert.h"

darknessNight_CppUnitTestFramework::AssertHelper darknessNight_CppUnitTestFramework::BasicAssert::helper;

void darknessNight_CppUnitTestFramework::BasicAssert::Fail(std::string message) {
	throw AssertFailException(message);
}

void darknessNight_CppUnitTestFramework::BasicAssert::Pass(std::string message) {
	throw AssertPassException(message);
}

int darknessNight_CppUnitTestFramework::BasicAssert::defaulComparer(const char * expected, const char * result) {
	return (strcmp(expected, result));
}

int darknessNight_CppUnitTestFramework::BasicAssert::defaulComparer(const wchar_t * expected, const wchar_t * result, std::string message) {
	return(wcscmp(expected, result));
}




