#pragma once
#include <TestsRunner/TestExecutor.h>
#include "ConvertTools.h"
#include "MessageLogger.h"
#include "TestReportConverter.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestPlatform;
using namespace Microsoft::VisualStudio::TestPlatform::ObjectModel;
using namespace Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter;
using namespace Microsoft::VisualStudio::TestPlatform::ObjectModel::Logging;

namespace darknessNight::CppUnitTest::VSAdapter {
	[ExtensionUri(gcnew String("executor://darknessNight_CppUnitTestExecutor/v1"))]
	public ref class TestsExecutor: public ITestExecutor{
	public:
		static Uri^ myUri = gcnew Uri(gcnew String("executor://darknessNight_CppUnitTestExecutor/v1"));
	private:
		MessageLogger^ logger = nullptr;
		bool m_cancelled;
		darknessNight::TestsRunner::TestExecutor* executor=new darknessNight::TestsRunner::TestExecutor;
	public:

		// Inherited via ITestExecutor
		virtual void RunTests(IEnumerable<ObjectModel::TestCase ^> ^tests, IRunContext ^runContext, IFrameworkHandle ^frameworkHandle){
			prepareConf(frameworkHandle);
			runTestsFromTestCases(tests, frameworkHandle);
		}

		void runTestsFromTestCases(System::Collections::Generic::IEnumerable<Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase ^> ^ tests, Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle) {
			Dictionary<String^, List<ObjectModel::TestCase^>^>^ groupsList = groupTestsBySource(tests);
			for each(auto group in groupsList) {
				if (m_cancelled)
					break;
				runTestAndSendTestResultsGroup(group, frameworkHandle);
			}
		}

		void prepareConf(Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle) {
			logger = gcnew MessageLogger(frameworkHandle);
			m_cancelled = false;
		}

		void runTestAndSendTestResultsGroup(System::Collections::Generic::KeyValuePair<System::String ^, System::Collections::Generic::List<Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase ^> ^> &group, Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle) {
			std::vector<std::string> testNames = getArrayWithTestNames(group);
			auto results = executor->runTests(ConvertTools::CliStringToCppString(group.Key), testNames);
			sendTestResultsToFramework(results, group, frameworkHandle);
		}

		void sendTestResultsToFramework(std::vector<darknessNight::CppUnitTestFramework::TestReport> &results, System::Collections::Generic::KeyValuePair<System::String ^, System::Collections::Generic::List<Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase ^> ^> &group, Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle) {
			for (auto result : results) {
				auto testResult = TestReportConverter::getVSResultFromReport(result, group.Key);
				frameworkHandle->RecordResult(testResult);
			}
		}

		std::vector<std::string> getArrayWithTestNames(System::Collections::Generic::KeyValuePair<System::String ^, System::Collections::Generic::List<Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase ^> ^> &group) {
			std::vector<std::string> testNames;
			testNames.reserve(group.Value->Count);
			for each(auto test in group.Value) {
				testNames.push_back(ConvertTools::CliStringToCppString(test->FullyQualifiedName));
			}
			return testNames;
		}

		Dictionary<String^, List<ObjectModel::TestCase^>^>^ groupTestsBySource(IEnumerable<ObjectModel::TestCase ^> ^ tests) {
			Dictionary<String^, List<ObjectModel::TestCase^>^>^ groupsList=gcnew Dictionary<String^, List<ObjectModel::TestCase^>^>();
			for each(auto test in tests) {
				if (!groupsList->ContainsKey(test->Source))
					groupsList->Add(test->Source, gcnew List<ObjectModel::TestCase^>);
				groupsList[test->Source]->Add(test);
			}
			return groupsList;
		}

		virtual void RunTests(IEnumerable<String ^> ^sources, IRunContext ^runContext, IFrameworkHandle ^frameworkHandle) {
			
		}

		virtual void Cancel(){
			m_cancelled = true;
			executor->stop();
		}
	};
}