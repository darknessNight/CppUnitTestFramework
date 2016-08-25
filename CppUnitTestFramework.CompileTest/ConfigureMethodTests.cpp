#include "ConfigureMethodTests.h"

using namespace darknessNight::CppUnitTestFramework;

void testClassSetUpAndTearDown() {
	auto testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName("TestSuiteTestMacro");
	checkTestFuncNotFalling(testSuite);
	checkRegisterSetUp(testSuite);
	checkRegisterTearDown(testSuite);
	std::cout << "Success";
}

void checkRegisterTearDown(darknessNight::CppUnitTestFramework::TestSuitePtr &testSuite)
{
	auto results = actRunTearDown(testSuite);
	assertRegisterTearDown(results);
}

const std::vector<darknessNight::CppUnitTestFramework::TestReport> actRunTearDown(darknessNight::CppUnitTestFramework::TestSuitePtr & testSuite)
{
	TestSuiteTestMacro::collapseTearDown = true;
	TestSuite::TestReportArray results = testSuite->runTestsAndGetReports();
	TestSuiteTestMacro::collapseTearDown = false;
	return results;
}

void assertRegisterTearDown(std::vector<darknessNight::CppUnitTestFramework::TestReport> &results)
{
	int textPos = results[0].getResult().getCause().find("TearDown");
	if (textPos<0)
		throw SpecialException("Test not have setted TearDown");
}

void checkRegisterSetUp(darknessNight::CppUnitTestFramework::TestSuitePtr &testSuite)
{
	std::vector<darknessNight::CppUnitTestFramework::TestReport> results=actRunSetUpMethod(testSuite);
	assertRegisterSetUp(results);
}

TestSuite::TestReportArray actRunSetUpMethod(darknessNight::CppUnitTestFramework::TestSuitePtr & testSuite)
{
	TestSuiteTestMacro::collapseSetup = true;
	TestSuite::TestReportArray results = testSuite->runTestsAndGetReports();
	TestSuiteTestMacro::collapseSetup = false;
	return results;
}

void assertRegisterSetUp(std::vector<darknessNight::CppUnitTestFramework::TestReport> &results)
{
	int textPos = results[0].getResult().getCause().find("SetUp");
	if (textPos<0)
		throw SpecialException("Test not have setted SetUp");
}

void checkTestFuncNotFalling(darknessNight::CppUnitTestFramework::TestSuitePtr &testSuite)
{
	auto results = testSuite->runTestsAndGetReports();
	if (results[0].getResult().isFailure())
		throw SpecialException("Test falling without reason");
}
