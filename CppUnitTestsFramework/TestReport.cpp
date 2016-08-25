#include "TestReport.h"

using namespace darknessNight::CppUnitTestFramework;

darknessNight::CppUnitTestFramework::TestReport::TestReport() :testResult(false) {}

TestResult darknessNight::CppUnitTestFramework::TestReport::getResult() {
	return testResult;
}

string darknessNight::CppUnitTestFramework::TestReport::getTestName() {
	return "TestName";
}

string darknessNight::CppUnitTestFramework::TestReport::getFile() {
	return testFile;
}

unsigned darknessNight::CppUnitTestFramework::TestReport::getLine() {
	return testLine;
}

string darknessNight::CppUnitTestFramework::TestReport::getSuiteName() {
	return testSuite;
}

TestCategory darknessNight::CppUnitTestFramework::TestReport::getCategory() {
	return testCategory;
}
