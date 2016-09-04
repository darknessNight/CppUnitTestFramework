#include "TestContainer.h"

using namespace darknessNight::CppUnitTestFramework;

darknessNight::CppUnitTestFramework::TestContainer::TestContainer() {
	unnamedSuite = std::shared_ptr<TestSuiteCreator>(new TestSuiteCreator("Unnamed"));
	addTestSuite(unnamedSuite);
}

void darknessNight::CppUnitTestFramework::TestContainer::addTestSuite(std::shared_ptr<TestSuiteCreator> creator) {
	std::string name = creator->getSuiteName();
	mapArray[name] = creator;
}

TestSuitePtr darknessNight::CppUnitTestFramework::TestContainer::getTestSuiteByName(std::string name) {
	name = setUnnamedIfNotHaveName(name);
	throwExceptionIfNotExistsSuite(name);
	return mapArray[name]->createInstance();
}

std::vector<TestSuitePtr> darknessNight::CppUnitTestFramework::TestContainer::getAllTestSuites() {
	std::vector<TestSuitePtr> suites;
	for (auto el : mapArray)
		suites.push_back(el.second->createInstance());
	return suites;
}

std::vector<std::string> darknessNight::CppUnitTestFramework::TestContainer::getTestSuiteList()
{
	std::vector<std::string> list;
	for (auto suite = mapArray.begin(); suite != mapArray.end(); suite++)
		list.push_back(suite->first);
	return list;
}

void darknessNight::CppUnitTestFramework::TestContainer::registerTestCaseToUnnamedSuite(TestCasePtr testCase) {
	registerTestCase("", testCase);
}

void darknessNight::CppUnitTestFramework::TestContainer::registerTestCase(std::string testSuite, TestCasePtr testCase) {
	checkTestSuiteName(testSuite);
	mapArray[testSuite]->registerTestCase(testCase);
}

void darknessNight::CppUnitTestFramework::TestContainer::registerSetUp(std::string testSuite, std::function<void()> setUp) {
	checkTestSuiteName(testSuite);
	mapArray[testSuite]->registerSetUp(setUp);
}

void darknessNight::CppUnitTestFramework::TestContainer::registerTearDown(std::string testSuite, std::function<void()> tearDown) {
	checkTestSuiteName(testSuite);
	mapArray[testSuite]->registerTearDown(tearDown);
}

void darknessNight::CppUnitTestFramework::TestContainer::checkTestSuiteName(std::string & testSuite)
{
	testSuite = setUnnamedIfNotHaveName(testSuite);
	throwExceptionIfNotExistsSuite(testSuite);
}

void darknessNight::CppUnitTestFramework::TestContainer::throwExceptionIfNotExistsSuite(std::string & testSuite)
{
	if (!keyExistsInArray(testSuite))
		throw NotFoundException("Not found suite with this name: " + testSuite + " in file:" __FILE__);
}

std::string darknessNight::CppUnitTestFramework::TestContainer::setUnnamedIfNotHaveName(std::string name) {
	if (name.size() <= 0)
		name = "Unnamed";
	return name;
}

bool darknessNight::CppUnitTestFramework::TestContainer::keyExistsInArray(std::string name) {
	return mapArray.find(name) != mapArray.end();
}
