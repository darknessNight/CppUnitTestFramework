#include "TestSuite.h"

using namespace darknessNight::CppUnitTestFramework;

std::string darknessNight::CppUnitTestFramework::TestSuite::getName() {
	setSuiteNameIfNotSetted();
	return suiteName;
}

void darknessNight::CppUnitTestFramework::TestSuite::addTestCase(TestCasePtr testCase) {
	testArray.push_back(testCase);
	testMap[testCase->getName()] = testCase;
}

void darknessNight::CppUnitTestFramework::TestSuite::setCategory(TestCategory cat) {
	testCategory = cat;
}

const TestCategory & darknessNight::CppUnitTestFramework::TestSuite::getCategory()
{
	return testCategory;
}

TestSuite::TestReportArray darknessNight::CppUnitTestFramework::TestSuite::runTestsAndGetReports() {
	TestReportArray returnTab;
	for each(TestCasePtr test in testArray) {
		TestReport report = prepareAndRunTest(test);
		returnTab.push_back(report);
	}
	return returnTab;
}

TestReport darknessNight::CppUnitTestFramework::TestSuite::runTestAndGetReport(std::string name) {
	TestCasePtr test = findTestFromName(name);
	return prepareAndRunTest(test);
}

std::vector<std::string> darknessNight::CppUnitTestFramework::TestSuite::getTestCaseList() {
	std::vector<string> array;
	for each(auto el in testMap)
		array.push_back(el.first);
	return array;
}

TestCasePtr darknessNight::CppUnitTestFramework::TestSuite::findTestFromName(string name) {
	TestCasePtr test = testMap[name];
	if (test == nullptr)
		throw NotFoundException("Not found TestCase in TestSuite");
	return test;
}

TestReport darknessNight::CppUnitTestFramework::TestSuite::prepareAndRunTest(TestCasePtr test) {
	prepareTestCase(test);
	return test->runTestAndGetReport();
}

void darknessNight::CppUnitTestFramework::TestSuite::prepareTestCase(TestCasePtr test) {
	test->setSetUpMethod(setUpMethod);
	test->setTearDownMethod(tearDownMethod);
	test->setCategory(testCategory);
	test->setSuite(getName());
}

void darknessNight::CppUnitTestFramework::TestSuite::setSuiteNameIfNotSetted()
{
	if (suiteName.size() <= 0) {
		suiteName = typeid(*this).name();
		suiteName = suiteName.substr(strlen("class "));
	}
}
