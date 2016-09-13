#pragma once
#include <TestsRunner/TestExecutor.h>
#include "ConvertTools.h"
#include "MessageLogger.h"
#include "TestReportConverter.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestPlatform;
using namespace ObjectModel;
using namespace ObjectModel::Adapter;
using namespace ObjectModel::Logging;

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

		void prepareConf(ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle) {
			logger = gcnew MessageLogger(frameworkHandle);
			m_cancelled = false;
		}

		void runTestsFromTestCases(IEnumerable<ObjectModel::TestCase ^> ^ tests, ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle) {
			Dictionary<String^, List<ObjectModel::TestCase^>^>^ groupsList = groupTestsBySource(tests);
			for each(auto group in groupsList) {
				if (m_cancelled)
					break;
				runTestAndSendTestResultsGroup(group, frameworkHandle);
			}
		}

		Dictionary<String^, List<ObjectModel::TestCase^>^>^ groupTestsBySource(IEnumerable<ObjectModel::TestCase ^> ^ tests) {
			Dictionary<String^, List<ObjectModel::TestCase^>^>^ groupsList = gcnew Dictionary<String^, List<ObjectModel::TestCase^>^>();
			for each(auto test in tests) {
				setNewKeyIfNotExists(test->Source, groupsList);
				groupsList[test->Source]->Add(test);
			}
			return groupsList;
		}

		void setNewKeyIfNotExists(System::String^ key, Dictionary<String^, List<ObjectModel::TestCase^>^>^ &groupsList) {
			if (!groupsList->ContainsKey(key))
				groupsList->Add(key, gcnew List<ObjectModel::TestCase^>);
		}

		void runTestAndSendTestResultsGroup(KeyValuePair<System::String ^, List<ObjectModel::TestCase ^> ^> &group, ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle) {
			std::vector<std::string> testNames = getArrayWithTestNames(group.Value);
			auto results = executor->runTests(ConvertTools::CliStringToCppString(group.Key), testNames);
			sendTestResultsToFramework(results, group, frameworkHandle);
		}

		void sendTestResultsToFramework(std::vector<darknessNight::CppUnitTestFramework::TestReport> &results, KeyValuePair<System::String ^, List<ObjectModel::TestCase ^> ^> &group, ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle) {
			for (auto result : results) {
				auto testResult = TestReportConverter::getVSResultFromReport(result, group.Key);
				frameworkHandle->RecordResult(testResult);
			}
		}

		std::vector<std::string> getArrayWithTestNames(List<ObjectModel::TestCase ^>^ group) {
			std::vector<std::string> testNames;
			testNames.reserve(group->Count);
			for each(auto test in group) {
				testNames.push_back(ConvertTools::CliStringToCppString(test->FullyQualifiedName));
			}
			return testNames;
		}

		virtual void RunTests(IEnumerable<String ^> ^sources, IRunContext ^runContext, IFrameworkHandle ^frameworkHandle) {
			throw gcnew System::NotImplementedException();			
		}

		virtual void Cancel(){
			m_cancelled = true;
			executor->stop();
		}
	};
}