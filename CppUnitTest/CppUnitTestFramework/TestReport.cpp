#include "TestReport.h"

using namespace darknessNight::CppUnitTestFramework;

TestReport::TestReport() :testResult(false) {}

TestResult& TestReport::getResult() {
	return testResult;
}

std::string TestReport::getTestName() {
	return testName;
}

std::string TestReport::getFile() {
	return testFile;
}

std::string TestReport::getFullName() {
	return testName + "(" + testSuite + ")";
}

unsigned TestReport::getLine() {
	return testLine;
}

std::string TestReport::getSuiteName() {
	return testSuite;
}

TestCategory TestReport::getCategory() {
	return testCategory;
}
