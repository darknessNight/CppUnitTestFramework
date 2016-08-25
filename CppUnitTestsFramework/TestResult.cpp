#include "TestResult.h"

darknessNight::CppUnitTestFramework::TestResult::TestResult(bool result) {
	isTestSuccess = result;
	errorMessage = "";
}

darknessNight::CppUnitTestFramework::TestResult::TestResult(const char * message) :TestResult(string(message)) {
}

darknessNight::CppUnitTestFramework::TestResult::TestResult(string message) {
	isTestSuccess = false;
	errorMessage = message;
}

string darknessNight::CppUnitTestFramework::TestResult::getFullMessage() {
	return errorCause + ": " + errorMessage;
}

string darknessNight::CppUnitTestFramework::TestResult::getErrorMessage() {
	return errorMessage;
}

string darknessNight::CppUnitTestFramework::TestResult::getCause() {
	return errorCause;
}

bool darknessNight::CppUnitTestFramework::TestResult::isSuccess() {
	return isTestSuccess == true;
}

bool darknessNight::CppUnitTestFramework::TestResult::isFailure() {
	return isTestSuccess == false;
}
