#include "TestSuiteInstanceCreator.h"

using namespace darknessNight::CppUnitTestFramework;

TestSuiteCreator::TestSuiteCreator(std::string name) {
	suiteName = name;
}

std::string TestSuiteCreator::getSuiteName() {
	return suiteName;
}

TestSuitePtr TestSuiteCreator::createInstance() {
	createIfNeeded();
	return testSuite;
}

void TestSuiteCreator::registerTestCase(TestCasePtr testCase) {
	if (testSuite == nullptr)
		testCasesArray.push_back(testCase);
	else
		testSuite->addTestCase(testCase);
}

void TestSuiteCreator::registerSetUp(std::function<void()> func) {
	setUp = func;
}

void TestSuiteCreator::registerTearDown(std::function<void()> func) {
	tearDown = func;
}

TestSuiteCreator::TestSuiteCreator() {}

void TestSuiteCreator::createIfNeeded() {
	testSuite = TestSuitePtr(new TestSuite(suiteName));
	prepareTestSuite();
}

void TestSuiteCreator::prepareTestSuite() {
	registerTestToSuite();
	registerConfigurationFuncs();
	saveCategory();
}

void TestSuiteCreator::saveCategory() {
	testSuite->setCategory(category);
}

void TestSuiteCreator::registerConfigurationFuncs()
{
	testSuite->setSetUpMethod(setUp);
	testSuite->setTearDownMethod(tearDown);
}

void TestSuiteCreator::registerTestToSuite() {
	for(auto testCase=testCasesArray.begin();testCase!=testCasesArray.end();testCase++)
		testSuite->addTestCase(*testCase);
	testCasesArray.clear();
}
