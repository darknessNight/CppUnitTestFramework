#include "TestContainer.h"

using namespace darknessNight_CppUnitTestFramework;

darknessNight_CppUnitTestFramework::TestContainer::TestContainer() {
	unnamedSuite = std::shared_ptr<TestSuiteCreator>(new TestSuiteInstanceCreator<TestSuite>("Unnamed"));
	addTestSuite(unnamedSuite);
}

void darknessNight_CppUnitTestFramework::TestContainer::addTestSuite(std::shared_ptr<TestSuiteCreator> creator) {
	std::string name = creator->getSuiteName();
	mapArray[name] = creator;
}

TestSuitePtr darknessNight_CppUnitTestFramework::TestContainer::getTestSuiteByName(std::string name) {
	name = setUnnamedIfNotHaveName(name);
	throwExceptionIfNotExistsSuite(name);
	return mapArray[name]->createInstance();
}

void darknessNight_CppUnitTestFramework::TestContainer::registerTestCaseToUnnamedSuite(TestCasePtr testCase) {
	registerTestCase("", testCase);
}

void darknessNight_CppUnitTestFramework::TestContainer::registerTestCase(std::string testSuite, TestCasePtr testCase) {
	checkTestSuiteName(testSuite);
	mapArray[testSuite]->registerTestCase(testCase);
}

void darknessNight_CppUnitTestFramework::TestContainer::registerSetUp(std::string testSuite, std::function<void()> setUp) {
	checkTestSuiteName(testSuite);
	mapArray[testSuite]->registerSetUp(setUp);
}

void darknessNight_CppUnitTestFramework::TestContainer::registerTearDown(std::string testSuite, std::function<void()> tearDown) {
	checkTestSuiteName(testSuite);
	mapArray[testSuite]->registerTearDown(tearDown);
}

void darknessNight_CppUnitTestFramework::TestContainer::checkTestSuiteName(std::string & testSuite)
{
	testSuite = setUnnamedIfNotHaveName(testSuite);
	throwExceptionIfNotExistsSuite(testSuite);
}

void darknessNight_CppUnitTestFramework::TestContainer::throwExceptionIfNotExistsSuite(std::string & testSuite)
{
	if (!keyExistsInArray(testSuite))
		throw NotFoundException("Not found suite with this name: " + testSuite + " in file:" __FILE__);
}

std::string darknessNight_CppUnitTestFramework::TestContainer::setUnnamedIfNotHaveName(std::string name) {
	if (name.size() <= 0)
		name = "Unnamed";
	return name;
}

bool darknessNight_CppUnitTestFramework::TestContainer::keyExistsInArray(std::string name) {
	return mapArray.find(name) != mapArray.end();
}
