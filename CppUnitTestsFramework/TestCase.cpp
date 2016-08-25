#include "TestCase.h"

using namespace darknessNight::CppUnitTestFramework;

void darknessNight::CppUnitTestFramework::TestCase::setName(string name) {
	report.testName = name;
}

darknessNight::CppUnitTestFramework::TestCase::TestCase() {}

string darknessNight::CppUnitTestFramework::TestCase::getName() {
	return report.testName;
}

void darknessNight::CppUnitTestFramework::TestCase::setFileAndLine(string file, unsigned int line) {
	report.testFile = file;
	report.testLine = line;
}

void darknessNight::CppUnitTestFramework::TestCase::setSuite(string suite) {
	report.testSuite = suite;
}

void darknessNight::CppUnitTestFramework::TestCase::setCategory(TestCategory cat) {
	report.testCategory = cat;
}

TestReport darknessNight::CppUnitTestFramework::TestCase::runTestAndGetReport() {
	TestResult result = runTest();
	return getReport(result);
}

TestReport darknessNight::CppUnitTestFramework::TestCase::getReport(TestResult result)
{
	TestReport returnReport = report;
	returnReport.testResult = result;
	return returnReport;
}

TestReport darknessNight::CppUnitTestFramework::TestCase::getReportWithoutResult()
{
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
