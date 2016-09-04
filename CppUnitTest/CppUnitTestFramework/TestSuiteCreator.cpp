#include "TestSuiteInstanceCreator.h"

using namespace darknessNight::CppUnitTestFramework;

darknessNight::CppUnitTestFramework::TestSuiteCreator::TestSuiteCreator(std::string name) {
	suiteName = name;
}

std::string darknessNight::CppUnitTestFramework::TestSuiteCreator::getSuiteName() {
	return suiteName;
}

TestSuitePtr darknessNight::CppUnitTestFramework::TestSuiteCreator::createInstance() {
	createIfNeeded();
	return testSuite;
}

void darknessNight::CppUnitTestFramework::TestSuiteCreator::registerTestCase(TestCasePtr testCase) {
	if (testSuite == nullptr)
		testCasesArray.push_back(testCase);
	else
		testSuite->addTestCase(testCase);
}

void darknessNight::CppUnitTestFramework::TestSuiteCreator::registerSetUp(std::function<void()> func) {
	setUp = func;
}

void darknessNight::CppUnitTestFramework::TestSuiteCreator::registerTearDown(std::function<void()> func) {
	tearDown = func;
}

darknessNight::CppUnitTestFramework::TestSuiteCreator::TestSuiteCreator() {}

void darknessNight::CppUnitTestFramework::TestSuiteCreator::createIfNeeded() {
	testSuite = TestSuitePtr(new TestSuite(suiteName));
	prepareTestSuite();
}

void darknessNight::CppUnitTestFramework::TestSuiteCreator::prepareTestSuite() {
	registerTestToSuite();
	registerConfigurationFuncs();
	saveCategory();
}

void darknessNight::CppUnitTestFramework::TestSuiteCreator::saveCategory() {
	testSuite->setCategory(category);
}

void darknessNight::CppUnitTestFramework::TestSuiteCreator::registerConfigurationFuncs()
{
	testSuite->setSetUpMethod(setUp);
	testSuite->setTearDownMethod(tearDown);
}

void darknessNight::CppUnitTestFramework::TestSuiteCreator::registerTestToSuite() {
	for(auto testCase=testCasesArray.begin();testCase!=testCasesArray.end();testCase++)
		testSuite->addTestCase(*testCase);
	testCasesArray.clear();
}
