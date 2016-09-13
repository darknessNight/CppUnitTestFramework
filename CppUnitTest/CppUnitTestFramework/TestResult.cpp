#include "TestResult.h"

darknessNight::CppUnitTestFramework::TestResult::TestResult(bool result) {
	isTestSuccess = result;
	errorMessage = "";
}

darknessNight::CppUnitTestFramework::TestResult::TestResult(const char * message) :TestResult(std::string(message)) {
}

darknessNight::CppUnitTestFramework::TestResult::TestResult(std::string message) {
	isTestSuccess = false;
	errorMessage = message;
}

std::string darknessNight::CppUnitTestFramework::TestResult::getFullMessage() {
	return errorCause + ": " + errorMessage;
}

std::string darknessNight::CppUnitTestFramework::TestResult::getErrorMessage() {
	return errorMessage;
}

std::string darknessNight::CppUnitTestFramework::TestResult::getCause() {
	return errorCause;
}

darknessNight::CppUnitTestFramework::TestResult::TimeDuration darknessNight::CppUnitTestFramework::TestResult::getDurationTime() {
	return time;
}

bool darknessNight::CppUnitTestFramework::TestResult::isSuccess() {
	return isTestSuccess == true;
}

bool darknessNight::CppUnitTestFramework::TestResult::isFailure() {
	return isTestSuccess == false;
}
