#include "TestCase.h"

using namespace darknessNight::CppUnitTestFramework;;

void darknessNight::CppUnitTestFramework::TestCase::setName(std::string name) {
	report.testName = name;
}

darknessNight::CppUnitTestFramework::TestCase::TestCase() {}

std::string darknessNight::CppUnitTestFramework::TestCase::getName() const {
	return report.testName;
}

void darknessNight::CppUnitTestFramework::TestCase::setFileAndLine(std::string file, unsigned int line) {
	report.testFile = file;
	report.testLine = line;
}

void darknessNight::CppUnitTestFramework::TestCase::setSuite(std::string suite) {
	report.testSuite = suite;
}

void darknessNight::CppUnitTestFramework::TestCase::setCategory(TestCategory cat) {
	report.testCategory = cat;
}

TestReport darknessNight::CppUnitTestFramework::TestCase::runTestAndGetReport() {
	TestResult result = runTest();
	return getReport(result);
}

TestReport darknessNight::CppUnitTestFramework::TestCase::getReport(TestResult result) const
{
	TestReport returnReport = report;
	returnReport.testResult = result;
	return returnReport;
}

TestReport darknessNight::CppUnitTestFramework::TestCase::getReportWithoutResult() const{
	return getReport(TestResult(false));
}

TestResult darknessNight::CppUnitTestFramework::TestCase::runTest() {
	prepareFunctionTester();
	TestResult result = functionTester->runTest();
	return result;
}

void darknessNight::CppUnitTestFramework::TestCase::prepareFunctionTester() {
	functionTester->setSetUpMethod(setUpMethod);
	functionTester->setTearDownMethod(tearDownMethod);
}
