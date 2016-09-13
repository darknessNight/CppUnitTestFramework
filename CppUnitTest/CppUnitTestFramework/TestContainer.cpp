#include "TestContainer.h"

using namespace darknessNight::CppUnitTestFramework;

TestContainer::TestContainer() {
	unnamedSuite = std::shared_ptr<TestSuiteCreator>(new TestSuiteCreator("Unnamed"));
	addTestSuite(unnamedSuite);
}

void TestContainer::addTestSuite(std::shared_ptr<TestSuiteCreator> creator) {
	std::string name = creator->getSuiteName();
	mapArray[name] = creator;
}

TestSuitePtr TestContainer::getTestSuiteByName(std::string name) {
	name = setUnnamedIfNotHaveName(name);
	throwExceptionIfNotExistsSuite(name);
	return mapArray[name]->createInstance();
}

std::vector<TestSuitePtr> TestContainer::getAllTestSuites() {
	std::vector<TestSuitePtr> suites;
	for (auto el : mapArray)
		suites.push_back(el.second->createInstance());
	return suites;
}

std::vector<std::string> TestContainer::getTestSuiteList()
{
	std::vector<std::string> list;
	for (auto suite = mapArray.begin(); suite != mapArray.end(); suite++)
		list.push_back(suite->first);
	return list;
}

void TestContainer::registerTestCaseToUnnamedSuite(TestCasePtr testCase) {
	registerTestCase("", testCase);
}

void TestContainer::registerTestCase(std::string testSuite, TestCasePtr testCase) {
	checkTestSuiteName(testSuite);
	mapArray[testSuite]->registerTestCase(testCase);
}

void TestContainer::registerSetUp(std::string testSuite, std::function<void()> setUp) {
	checkTestSuiteName(testSuite);
	mapArray[testSuite]->registerSetUp(setUp);
}

void TestContainer::registerTearDown(std::string testSuite, std::function<void()> tearDown) {
	checkTestSuiteName(testSuite);
	mapArray[testSuite]->registerTearDown(tearDown);
}

void TestContainer::checkTestSuiteName(std::string & testSuite)
{
	testSuite = setUnnamedIfNotHaveName(testSuite);
	throwExceptionIfNotExistsSuite(testSuite);
}

void TestContainer::throwExceptionIfNotExistsSuite(std::string & testSuite)
{
	if (!keyExistsInArray(testSuite))
		throw NotFoundException("Not found suite with this name: " + testSuite + " in file:" __FILE__);
}

std::string TestContainer::setUnnamedIfNotHaveName(std::string name) {
	if (name.size() <= 0)
		name = "Unnamed";
	return name;
}

bool TestContainer::keyExistsInArray(std::string name) {
	return mapArray.find(name) != mapArray.end();
}
