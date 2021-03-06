#include "stdafx.h"
#include "TestDiscover.h"
#include <TestsRunner/ConsoleMessageLogger.h>
using namespace darknessNight::Filesystem;
using namespace darknessNight::SharedLibrary;

void darknessNight::CppUnitTest::VSAdapter::TestDiscover::DiscoverTests(IEnumerable<String^>^ sources, IDiscoveryContext ^ discoveryContext, IMessageLogger ^ messLogger, ITestCaseDiscoverySink ^ discoverySink) {
	getTests(sources, discoveryContext, messLogger, discoverySink);
}

List<ObjectModel::TestCase^>^ darknessNight::CppUnitTest::VSAdapter::TestDiscover::getTests(IEnumerable<String^>^ sources, IDiscoveryContext ^ discoveryContext, IMessageLogger ^ messLogger, ITestCaseDiscoverySink ^ discoverySink) {
	prepareToFindTests(messLogger);
	auto cases = findAllTests(sources, discoverySink);
	logEndFindTest();
	return cases;
}

void darknessNight::CppUnitTest::VSAdapter::TestDiscover::logEndFindTest() {
	logger->sendInfo("Tests found: " + countOfTests.ToString());
	logger->sendInfo("----CppUnitTestAdapter:Ended----");
}

void darknessNight::CppUnitTest::VSAdapter::TestDiscover::prepareToFindTests(Microsoft::VisualStudio::TestPlatform::ObjectModel::Logging::IMessageLogger ^ messLogger) {
	logger = gcnew MessageLogger(messLogger);
	countOfTests = 0;
	logger->sendInfo("----CppUnitTestAdapter:Started----");
}

List<ObjectModel::TestCase^>^ darknessNight::CppUnitTest::VSAdapter::TestDiscover::findAllTests(IEnumerable<System::String^>^ sources, ITestCaseDiscoverySink ^ discoverySink) {
	List<ObjectModel::TestCase^>^ cases = gcnew List<ObjectModel::TestCase^>();
	for each (auto path in sources) {
		searchTestsInFile(path, discoverySink, cases);
	}
	return cases;
}

void darknessNight::CppUnitTest::VSAdapter::TestDiscover::searchTestsInFile(System::String ^& path, Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter::ITestCaseDiscoverySink ^ discoverySink, System::Collections::Generic::List<Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase^>^ cases) {
	auto discover=getNativeDiscover();
	readTestsFromFile(path, discover);
	saveTestsAsTestCases(discover, path, discoverySink, cases);
	freeLoadedLibraries(discover);
}

darknessNight::TestsRunner::TestDiscover darknessNight::CppUnitTest::VSAdapter::TestDiscover::getNativeDiscover() {
	auto log = std::make_shared<CppMessageLogger>(gcroot<MessageLogger^>(logger));
	auto library = std::make_shared<DynamicLibrary>();
	auto directory = std::make_shared<Directory>(".");
	return darknessNight::TestsRunner::TestDiscover(directory, library, log);
}

void darknessNight::CppUnitTest::VSAdapter::TestDiscover::freeLoadedLibraries(darknessNight::TestsRunner::TestDiscover &discover) {
	discover.safeClear();
}

void darknessNight::CppUnitTest::VSAdapter::TestDiscover::readTestsFromFile(System::String ^& path, darknessNight::TestsRunner::TestDiscover & discover) {
	discover.findInFile(ConvertTools::CliStringToCppString(path));
}

void darknessNight::CppUnitTest::VSAdapter::TestDiscover::saveTestsAsTestCases(darknessNight::TestsRunner::TestDiscover & discover, System::String ^& path, Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter::ITestCaseDiscoverySink ^ discoverySink, System::Collections::Generic::List<Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase^>^ cases) {
	for (auto test : discover.getTestsList()) {
#ifdef ADDITIONAL_LOGS
		logger->sendMessage("Found test: " + testCase->getName());
#endif
		saveAndSendTestCase(test, path, discoverySink, cases);
		countOfTests++;
	}
}

void darknessNight::CppUnitTest::VSAdapter::TestDiscover::saveAndSendTestCase(darknessNight::CppUnitTestFramework::TestCasePtr & test, System::String ^& path, Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter::ITestCaseDiscoverySink ^ discoverySink, System::Collections::Generic::List<Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase^>^ cases) {
	ObjectModel::TestCase^ testCase = TestReportConverter::getVSTestCaseFromReport(test->getReportWithoutResult(), path);
	if (discoverySink != nullptr)
		discoverySink->SendTestCase(testCase);
	cases->Add(testCase);
}
