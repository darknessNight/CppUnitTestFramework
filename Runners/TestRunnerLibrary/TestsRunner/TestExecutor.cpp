#include "TestExecutor.h"


darknessNight::TestsRunner::TestExecutor::TestExecutor(std::shared_ptr<Directory> dir, std::shared_ptr<DynamicLibrary> dynLibs, std::shared_ptr<MessageLogger> messageLogger)
:discover(dir, dynLibs, messageLogger) {
	logger = messageLogger;
}

darknessNight::TestsRunner::TestExecutor::~TestExecutor() {
}

void darknessNight::TestsRunner::TestExecutor::stop() {
	running = false;
}

void darknessNight::TestsRunner::TestExecutor::safeClear() {
	discover.safeClear();
}

std::vector<TestReport> darknessNight::TestsRunner::TestExecutor::runTests(std::vector<TestCasePtr> testCases) {
	logger->sendMessage("Run tests from testcases");
	running = true;
	std::vector<TestReport> reports;
	for(auto test : testCases) {
		if(!running)
			break;
		reports.push_back(runTest(test));
	}
	return reports;
}

TestReport darknessNight::TestsRunner::TestExecutor::runTest(TestCasePtr testCase) {
#ifdef ADDITIONAL_LOGS
	logger->sendMessage("Runned test: " + testCase->getName());
#endif
	return testCase->runTestAndGetReport();
}

std::vector<TestReport> darknessNight::TestsRunner::TestExecutor::runTests(TestSuitePtr testSuite) {
	return runTests(testSuite->getTestCases());
}

std::vector<TestReport> darknessNight::TestsRunner::TestExecutor::runTests(std::string path, std::vector<std::string> names) {
	logRunTestInPath(path);
	auto tests = getAllTestsInFile(path);
	return filterAndRunTests(tests, names);
}

void darknessNight::TestsRunner::TestExecutor::logRunTestInPath(std::string path) {
	logger->sendMessage("Run tests in module: " + path);
}

std::vector<TestReport> darknessNight::TestsRunner::TestExecutor::runTestsFromFile(std::string path) {
	logRunTestInPath(path);
	std::vector<TestReport> reports;
	for (auto test : getAllTestsInFile(path))
		reports.push_back(runTest(test));
	return reports;
}

std::vector<TestCasePtr> darknessNight::TestsRunner::TestExecutor::getAllTestsInFile(std::string& path) {
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

TestReport darknessNight::TestsRunner::TestExecutor::runTest(TestSuitePtr testSuite, std::string testName) {
	return runTest(testSuite->getTestCase(testName));
}
