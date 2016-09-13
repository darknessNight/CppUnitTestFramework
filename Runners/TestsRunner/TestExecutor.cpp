#include "TestExecutor.h"

darknessNight::TestsRunner::TestExecutor::~TestExecutor() {
	DIContainer::Get<DynamicLibrary>()->freeAllLibraries();
}

void darknessNight::TestsRunner::TestExecutor::stop() {
	running = false;
}

std::vector<TestReport> darknessNight::TestsRunner::TestExecutor::runTests(std::vector<TestCasePtr> testCases) {
	running = true;
	std::vector<TestReport> reports;
	for(auto test : testCases) {
		if(!running)
			break;
		reports.push_back(runTest(test));
	}
	return reports;
}

std::vector<TestReport> darknessNight::TestsRunner::TestExecutor::runTests(TestSuitePtr testSuite) {
	return runTests(testSuite->getTestCases());
}

std::vector<TestReport> darknessNight::TestsRunner::TestExecutor::runTests(std::string path, std::vector<std::string> names) {
	auto tests = getAllTestsInFile(path);
	return filterAndRunTests(tests, names);
}

std::vector<TestReport> darknessNight::TestsRunner::TestExecutor::runTestsFromFile(std::string path) {
	std::vector<TestReport> reports;
	for (auto test : getAllTestsInFile(path))
		reports.push_back(runTest(test));
	return reports;
}

std::vector<TestCasePtr> darknessNight::TestsRunner::TestExecutor::getAllTestsInFile(std::string& path) {
	TestsDiscover discover;
	discover.findInFile(path);
	return discover.getTestsList();
}

std::vector<TestReport> darknessNight::TestsRunner::TestExecutor::filterAndRunTests(std::vector<TestCasePtr> tests, std::vector<std::string>& names) {
	running = true;
	std::vector<TestReport> reports;
	for(auto test : tests) {
		if(!running)
			break;
		runTestWithNameHasInFilter(names, test, reports);
	}
	return reports;
}

void darknessNight::TestsRunner::TestExecutor::runTestWithNameHasInFilter(std::vector<std::string>& names, TestCasePtr& test, std::vector<TestReport>& reports) {
	for(auto name = names.begin(); name != names.end(); name++)
		if(isTestHasPassFullname(test, *name)) {
			runTestAndSaveReport(reports, test);
			deleteNameFromNamesTab(name, names);
			break;
		}
}

void darknessNight::TestsRunner::TestExecutor::deleteNameFromNamesTab(std::vector<std::string>::iterator& name, std::vector<std::string>& names) {
	swap(*name, *names.rbegin());
	names.pop_back();
}

bool darknessNight::TestsRunner::TestExecutor::isTestHasPassFullname(TestCasePtr& test, std::string& name) {
	return test->getReportWithoutResult().getFullName() == name;
}

void darknessNight::TestsRunner::TestExecutor::runTestAndSaveReport(std::vector<TestReport>& reports, TestCasePtr& test) {
	reports.push_back(test->runTestAndGetReport());
}

TestReport darknessNight::TestsRunner::TestExecutor::runTest(TestCasePtr testCase) {
	return testCase->runTestAndGetReport();
}

TestReport darknessNight::TestsRunner::TestExecutor::runTest(TestSuitePtr testSuite, std::string testName) {
	return runTest(testSuite->getTestCase(testName));
}
