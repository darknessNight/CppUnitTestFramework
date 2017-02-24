#include "BasicAssert.h"

darknessNight::CppUnitTestFramework::AssertHelper darknessNight::CppUnitTestFramework::BasicAssert::helper;

void darknessNight::CppUnitTestFramework::BasicAssert::Fail(std::string message) {
	throw AssertFailException(message);
}

void darknessNight::CppUnitTestFramework::BasicAssert::Pass(std::string message) {
	throw AssertPassException(message);
}

int darknessNight::CppUnitTestFramework::BasicAssert::defaulComparer(const char * expected, const char * result) {
	return (strcmp(expected, result));
}

int darknessNight::CppUnitTestFramework::BasicAssert::defaulComparer(const wchar_t * expected, const wchar_t * result, std::string message) {
	return(wcscmp(expected, result));
}