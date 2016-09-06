#include "TestResult.h"

void darknessNight::CppUnitTestFramework::TestResult::setTime(std::chrono::nanoseconds time) {
	this->time = time;
}

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

std::chrono::nanoseconds darknessNight::CppUnitTestFramework::TestResult::getTime() {
	return time;
}

bool darknessNight::CppUnitTestFramework::TestResult::isSuccess() {
	return isTestSuccess == true;
}

bool darknessNight::CppUnitTestFramework::TestResult::isFailure() {
	return isTestSuccess == false;
}
