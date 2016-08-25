#include "TestSuiteInstanceCreator.h"

using namespace darknessNight_CppUnitTestFramework;

std::string darknessNight_CppUnitTestFramework::TestSuiteCreator::getSuiteName() {
	return suiteName;
}

TestSuitePtr darknessNight_CppUnitTestFramework::TestSuiteCreator::createInstance() {
	createIfNeeded();
	return testSuite;
}

void darknessNight_CppUnitTestFramework::TestSuiteCreator::registerTestCase(TestCasePtr testCase) {
	if (testSuite == nullptr)
		testCasesArray.push_back(testCase);
	else
		testSuite->addTestCase(testCase);
}

void darknessNight_CppUnitTestFramework::TestSuiteCreator::registerSetUp(std::function<void()> func) {
	setUp = func;
}

void darknessNight_CppUnitTestFramework::TestSuiteCreator::registerTearDown(std::function<void()> func) {
	tearDown = func;
}

void darknessNight_CppUnitTestFramework::TestSuiteCreator::prepareTestSuite() {
	registerTestToSuite();
	registerConfigurationFuncs();
	saveCategory();
}

void darknessNight_CppUnitTestFramework::TestSuiteCreator::saveCategory() {
	testSuite->setCategory(category);
}

void darknessNight_CppUnitTestFramework::TestSuiteCreator::registerConfigurationFuncs()
{
	testSuite->setSetUpMethod(setUp);
	testSuite->setTearDownMethod(tearDown);
}

void darknessNight_CppUnitTestFramework::TestSuiteCreator::registerTestToSuite() {
	for(auto testCase=testCasesArray.begin();testCase!=testCasesArray.end();testCase++)
		testSuite->addTestCase(*testCase);
	testCasesArray.clear();
}
