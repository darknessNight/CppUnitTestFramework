#include "TestSuite.h"
#include "Exceptions.h"

using namespace darknessNight_CppUnitTestFramework;

std::string darknessNight_CppUnitTestFramework::TestSuite::getName() {
	setSuiteNameIfNotSetted();
	return suiteName;
}

void darknessNight_CppUnitTestFramework::TestSuite::addTestCase(TestCasePtr testCase) {
	testArray.push_back(testCase);
	testMap[testCase->getName()] = testCase;
}

void darknessNight_CppUnitTestFramework::TestSuite::setCategory(TestCategory cat) {
	testCategory = cat;
}

const TestCategory & darknessNight_CppUnitTestFramework::TestSuite::getCategory()
{
	return testCategory;
}

TestSuite::TestReportArray darknessNight_CppUnitTestFramework::TestSuite::runTestsAndGetReports() {
	TestReportArray returnTab;
	for(auto test = testArray.begin(); test!=testArray.end();test++) {
		TestReport report = prepareAndRunTest(*test);
		returnTab.push_back(report);
	}
	return returnTab;
}

TestReport darknessNight_CppUnitTestFramework::TestSuite::runTestAndGetReport(std::string name) {
	TestCasePtr test = findTestFromName(name);
	return prepareAndRunTest(test);
}

const std::shared_ptr<const TestCase> darknessNight_CppUnitTestFramework::TestSuite::getTestCase(std::string name){
	return findTestFromName(name);
}

std::vector<std::string> darknessNight_CppUnitTestFramework::TestSuite::getTestCaseList() {
	std::vector<std::string> array;
	for(auto el=testMap.begin();el!=testMap.end();el++)
		array.push_back(el->first);
	return array;
}

TestCasePtr darknessNight_CppUnitTestFramework::TestSuite::findTestFromName(std::string name) {
	TestCasePtr test = testMap[name];
	if (test == nullptr)
		throw NotFoundException("Not found TestCase in TestSuite");
	return test;
}

TestReport darknessNight_CppUnitTestFramework::TestSuite::prepareAndRunTest(TestCasePtr test) {
	prepareTestCase(test);
	return test->runTestAndGetReport();
}

void darknessNight_CppUnitTestFramework::TestSuite::prepareTestCase(TestCasePtr test) {
	test->setSetUpMethod(setUpMethod);
	test->setTearDownMethod(tearDownMethod);
	test->setCategory(testCategory);
	test->setSuite(getName());
}

void darknessNight_CppUnitTestFramework::TestSuite::setSuiteNameIfNotSetted()
{
	if (suiteName.size() <= 0) {
		suiteName = typeid(*this).name();
		suiteName = suiteName.substr(std::string("class ").size());
	}
}