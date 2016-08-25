#include "TestCase.h"

using namespace darknessNight_CppUnitTestFramework;

void darknessNight_CppUnitTestFramework::TestCase::setName(std::string name) {
	report.testName = name;
}

darknessNight_CppUnitTestFramework::TestCase::TestCase() {}

std::string darknessNight_CppUnitTestFramework::TestCase::getName() const {
	return report.testName;
}

void darknessNight_CppUnitTestFramework::TestCase::setFileAndLine(std::string file, unsigned int line) {
	report.testFile = file;
	report.testLine = line;
}

void darknessNight_CppUnitTestFramework::TestCase::setSuite(std::string suite) {
	report.testSuite = suite;
}

void darknessNight_CppUnitTestFramework::TestCase::setCategory(TestCategory cat) {
	report.testCategory = cat;
}

TestReport darknessNight_CppUnitTestFramework::TestCase::runTestAndGetReport() {
	TestResult result = runTest();
	return getReport(result);
}

TestReport darknessNight_CppUnitTestFramework::TestCase::getReport(TestResult result) const
{
	TestReport returnReport = report;
	returnReport.testResult = result;
	return returnReport;
}

TestReport darknessNight_CppUnitTestFramework::TestCase::getReportWithoutResult() const{
	return getReport(TestResult(false));
}

TestResult darknessNight_CppUnitTestFramework::TestCase::runTest() {
	prepareFunctionTester();
	TestResult result = functionTester->runTest();
	return result;
}

void darknessNight_CppUnitTestFramework::TestCase::prepareFunctionTester() {
	functionTester->setSetUpMethod(setUpMethod);
	functionTester->setTearDownMethod(tearDownMethod);
}
