#include "TestResult.h"

darknessNight_CppUnitTestFramework::TestResult::TestResult(bool result) {
	isTestSuccess = result;
	errorMessage = "";
}

darknessNight_CppUnitTestFramework::TestResult::TestResult(const char * message) :TestResult(std::string(message)) {
}

darknessNight_CppUnitTestFramework::TestResult::TestResult(std::string message) {
	isTestSuccess = false;
	errorMessage = message;
}

std::string darknessNight_CppUnitTestFramework::TestResult::getFullMessage() {
	return errorCause + ": " + errorMessage;
}

std::string darknessNight_CppUnitTestFramework::TestResult::getErrorMessage() {
	return errorMessage;
}

std::string darknessNight_CppUnitTestFramework::TestResult::getCause() {
	return errorCause;
}

bool darknessNight_CppUnitTestFramework::TestResult::isSuccess() {
	return isTestSuccess == true;
}

bool darknessNight_CppUnitTestFramework::TestResult::isFailure() {
	return isTestSuccess == false;
}
