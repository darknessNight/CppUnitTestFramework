#include "stdafx.h"
#include "TestsExecutor.h"
#include "TestReportConverter.h"
#include <TestsRunner/ConsoleMessageLogger.h>

void darknessNight::CppUnitTest::VSAdapter::TestExecutor::RunTests(IEnumerable<ObjectModel::TestCase^>^ tests, IRunContext ^ runContext, IFrameworkHandle ^ frameworkHandle) {
	prepareConf(frameworkHandle);
	runTestsFromTestCases(tests, frameworkHandle);
	showEndMessage();
}

void darknessNight::CppUnitTest::VSAdapter::TestExecutor::prepareConf(ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle) {
	logger = gcnew MessageLogger(frameworkHandle);
	auto cppLogger = std::make_shared<CppMessageLogger>(gcroot<MessageLogger^>(logger));
	executor = new darknessNight::TestsRunner::TestExecutor(std::make_shared<Directory>("."), std::make_shared<DynamicLibrary>(),cppLogger);
	m_cancelled = false;
	runnedTests = 0;
	logger->sendInfo("Start running test:CppUnitTestAdapter");
}

void darknessNight::CppUnitTest::VSAdapter::TestExecutor::showEndMessage() {
	logger->sendInfo("CppUnitTestAdapter: runned tests: " + runnedTests.ToString());
	delete executor;
}

void darknessNight::CppUnitTest::VSAdapter::TestExecutor::runTestsFromTestCases(IEnumerable<ObjectModel::TestCase^>^ tests, ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle) {
	Dictionary<String^, List<ObjectModel::TestCase^>^>^ groupsList = groupTestsBySource(tests);
	for each(auto group in groupsList) {
		if (m_cancelled)
			break;
		runTestAndSendTestResultsGroup(group, frameworkHandle);
	}
}

Dictionary<String^, List<ObjectModel::TestCase^>^>^ darknessNight::CppUnitTest::VSAdapter::TestExecutor::groupTestsBySource(IEnumerable<ObjectModel::TestCase^>^ tests) {
	Dictionary<String^, List<ObjectModel::TestCase^>^>^ groupsList = gcnew Dictionary<String^, List<ObjectModel::TestCase^>^>();
	for each(auto test in tests) {
		setNewKeyIfNotExists(test->Source, groupsList);
		groupsList[test->Source]->Add(test);
	}
	return groupsList;
}

void darknessNight::CppUnitTest::VSAdapter::TestExecutor::setNewKeyIfNotExists(System::String ^ key, Dictionary<String^, List<ObjectModel::TestCase^>^>^& groupsList) {
	if (!groupsList->ContainsKey(key))
		groupsList->Add(key, gcnew List<ObjectModel::TestCase^>);
}

void darknessNight::CppUnitTest::VSAdapter::TestExecutor::runTestAndSendTestResultsGroup(KeyValuePair<System::String^, List<ObjectModel::TestCase^>^>& group, ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle) {
	std::vector<std::string> testNames = getArrayWithTestNames(group.Value);
	auto results = executor->runTests(ConvertTools::CliStringToCppString(group.Key), testNames);
	sendTestResultsToFramework(results, group.Key, frameworkHandle);
}

void darknessNight::CppUnitTest::VSAdapter::TestExecutor::sendTestResultsToFramework(std::vector<darknessNight::CppUnitTestFramework::TestReport>& results, System::String ^ path, ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle) {
	logger->sendInfo("Run test in path: " + path);
	for (auto result : results) {
		runnedTests++;
		auto testResult = TestReportConverter::getVSResultFromReport(result, path);
		frameworkHandle->RecordResult(testResult);
	}
}

std::vector<std::string> darknessNight::CppUnitTest::VSAdapter::TestExecutor::getArrayWithTestNames(List<ObjectModel::TestCase^>^ group) {
	std::vector<std::string> testNames;
	testNames.reserve(group->Count);
	for each(auto test in group) {
		testNames.push_back(ConvertTools::CliStringToCppString(test->FullyQualifiedName));
	}
	return testNames;
}

void darknessNight::CppUnitTest::VSAdapter::TestExecutor::RunTests(IEnumerable<String^>^ sources, IRunContext ^ runContext, IFrameworkHandle ^ frameworkHandle) {
	prepareConf(frameworkHandle);
	for each(auto path in sources) {
		runTestsInFileAndSendReportsToFramework(path, frameworkHandle);
	}
	showEndMessage();
}

void darknessNight::CppUnitTest::VSAdapter::TestExecutor::runTestsInFileAndSendReportsToFramework(System::String ^ path, Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle) {
	auto results = executor->runTestsFromFile(ConvertTools::CliStringToCppString(path));
	sendTestResultsToFramework(results, path, frameworkHandle);
}

void darknessNight::CppUnitTest::VSAdapter::TestExecutor::Cancel() {
	m_cancelled = true;
	executor->stop();
}
