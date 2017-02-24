#include "TestSuite.h"
#include "Exceptions.h"

using namespace darknessNight::CppUnitTestFramework;

std::string TestSuite::getName() {
	setSuiteNameIfNotSetted();
	return suiteName;
}

TestSuite::TestSuite() {}

TestSuite::TestSuite(std::string name) { suiteName = name; }

void TestSuite::addTestCase(TestCasePtr testCase) {
	testArray.push_back(testCase);
	testMap[testCase->getName()] = testCase;
}

void TestSuite::setCategory(TestCategory cat) {
	testCategory = cat;
}

const TestCategory & TestSuite::getCategory()
{
	return testCategory;
}

TestSuite::TestReportArray TestSuite::runTestsAndGetReports() {
	TestReportArray returnTab;
	for(auto test = testArray.begin(); test!=testArray.end();test++) {
		TestReport report = prepareAndRunTest(*test);
		returnTab.push_back(report);
	}
	return returnTab;
}

TestReport TestSuite::runTestAndGetReport(std::string name) {
	TestCasePtr test = findTestFromName(name);
	return prepareAndRunTest(test);
}

TestCasePtr TestSuite::getTestCase(std::string name){
	auto test= findTestFromName(name);
	prepareTestCase(test);
	return test;
}

std::vector<TestCasePtr> TestSuite::getTestCases() {
	for (auto test : testArray)
		prepareTestCase(test);
	return testArray;
}

std::vector<std::string> TestSuite::getTestCaseList() {
	std::vector<std::string> array;
	for(auto el=testMap.begin();el!=testMap.end();el++)
		array.push_back(el->first);
	return array;
}

TestCasePtr TestSuite::findTestFromName(std::string name) {
	TestCasePtr test = testMap[name];
	if (test == nullptr)
		throw NotFoundException("Not found TestCase in TestSuite");
	return test;
}

TestReport TestSuite::prepareAndRunTest(TestCasePtr test) {
	prepareTestCase(test);
	return test->runTestAndGetReport();
}

void TestSuite::prepareTestCase(TestCasePtr test) {
	test->setSetUpMethod(setUpMethod);
	test->setTearDownMethod(tearDownMethod);
	test->setCategory(testCategory);
	test->setSuite(getName());
}

void TestSuite::setSuiteNameIfNotSetted()
{
	if (suiteName.size() <= 0) {
		suiteName = typeid(*this).name();
		suiteName = suiteName.substr(std::string("class ").size());
	}
}
