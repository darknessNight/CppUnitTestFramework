#include "TestReport.h"

using namespace darknessNight_CppUnitTestFramework;

darknessNight_CppUnitTestFramework::TestReport::TestReport() :testResult(false) {}

TestResult darknessNight_CppUnitTestFramework::TestReport::getResult() {
	return testResult;
}

std::string darknessNight_CppUnitTestFramework::TestReport::getTestName() {
	return testName;
}

std::string darknessNight_CppUnitTestFramework::TestReport::getFile() {
	return testFile;
}

unsigned darknessNight_CppUnitTestFramework::TestReport::getLine() {
	return testLine;
}

std::string darknessNight_CppUnitTestFramework::TestReport::getSuiteName() {
	return testSuite;
}

TestCategory darknessNight_CppUnitTestFramework::TestReport::getCategory() {
	return testCategory;
}
