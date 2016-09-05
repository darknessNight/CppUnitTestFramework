#include "TestReport.h"

using namespace darknessNight::CppUnitTestFramework;

darknessNight::CppUnitTestFramework::TestReport::TestReport() :testResult(false) {}

TestResult darknessNight::CppUnitTestFramework::TestReport::getResult() {
	return testResult;
}

std::string darknessNight::CppUnitTestFramework::TestReport::getTestName() {
	return testName;
}

std::string darknessNight::CppUnitTestFramework::TestReport::getFile() {
	return testFile;
}

std::string darknessNight::CppUnitTestFramework::TestReport::getFullName() {
	return testName + "(" + testSuite + ")";
}

unsigned darknessNight::CppUnitTestFramework::TestReport::getLine() {
	return testLine;
}

std::string darknessNight::CppUnitTestFramework::TestReport::getSuiteName() {
	return testSuite;
}

TestCategory darknessNight::CppUnitTestFramework::TestReport::getCategory() {
	return testCategory;
}
