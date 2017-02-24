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
	public ref class TestExecutor : public ITestExecutor {
	public:
		static Uri^ myUri = gcnew Uri(gcnew String("executor://darknessNight_CppUnitTestExecutor/v1"));
	private:
		int runnedTests = 0;
		MessageLogger^ logger = nullptr;
		bool m_cancelled;
		darknessNight::TestsRunner::TestExecutor* executor;

	public:
		virtual void RunTests(IEnumerable<ObjectModel::TestCase ^> ^tests, IRunContext ^runContext, IFrameworkHandle ^frameworkHandle);
		virtual void RunTests(IEnumerable<String ^> ^sources, IRunContext ^runContext, IFrameworkHandle ^frameworkHandle);
		virtual void Cancel();
	private:
		void prepareConf(ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle);
		void runTestsFromTestCases(IEnumerable<ObjectModel::TestCase ^> ^ tests, ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle);
		Dictionary<String^, List<ObjectModel::TestCase^>^>^ groupTestsBySource(IEnumerable<ObjectModel::TestCase ^> ^ tests);
		void setNewKeyIfNotExists(System::String^ key, Dictionary<String^, List<ObjectModel::TestCase^>^>^ &groupsList);
		void runTestAndSendTestResultsGroup(KeyValuePair<System::String ^, List<ObjectModel::TestCase ^> ^> &group, ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle);
		void sendTestResultsToFramework(std::vector<darknessNight::CppUnitTestFramework::TestReport> &results, System::String^ path, ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle);
		std::vector<std::string> getArrayWithTestNames(List<ObjectModel::TestCase ^>^ group);
		void runTestsInFileAndSendReportsToFramework(System::String ^ path, Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter::IFrameworkHandle ^ frameworkHandle);
		void showEndMessage();
	};
}