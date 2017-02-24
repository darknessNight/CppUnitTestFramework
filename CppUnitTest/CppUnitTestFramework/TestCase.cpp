#include "TestCase.h"

using namespace darknessNight::CppUnitTestFramework;;

void TestCase::setName(std::string name) {
	report.testName = name;
}

TestCase::TestCase() {}

std::string TestCase::getName() const {
	return report.testName;
}

void TestCase::setFileAndLine(std::string file, unsigned int line) {
	report.testFile = file;
	report.testLine = line;
}

void TestCase::setSuite(std::string suite) {
	report.testSuite = suite;
}

void TestCase::setCategory(TestCategory cat) {
	report.testCategory = cat;
}

TestReport TestCase::runTestAndGetReport() {
	TestResult result = runTest();
	return getReport(result);
}

TestReport TestCase::getReport(TestResult result) const
{
	TestReport returnReport = report;
	returnReport.testResult = result;
	return returnReport;
}

TestReport TestCase::getReportWithoutResult() const{
	return getReport(TestResult(false));
}

TestResult TestCase::runTest() {
	prepareFunctionTester();
	TestResult result = functionTester->runTest();
	return result;
}

void TestCase::prepareFunctionTester() {
	functionTester->setSetUpMethod(setUpMethod);
	functionTester->setTearDownMethod(tearDownMethod);
}
