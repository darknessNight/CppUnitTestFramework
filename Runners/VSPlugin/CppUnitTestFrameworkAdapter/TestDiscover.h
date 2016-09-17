#pragma once
#include <vector>
#include <TestsRunner/TestDiscover.h>
#include "ConvertTools.h"
#include "MessageLogger.h"
#include "TestReportConverter.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestPlatform;
using namespace Microsoft::VisualStudio::TestPlatform::ObjectModel;
using namespace Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter;
using namespace Microsoft::VisualStudio::TestPlatform::ObjectModel::Logging;
using namespace System::Threading;

namespace darknessNight::CppUnitTest::VSAdapter {
	[DefaultExecutorUri(gcnew String("executor://darknessNight_CppUnitTestExecutor/v1"))]
	[FileExtension(".dll")]
	public ref class TestDiscover : public ITestDiscoverer {
	private:
		MessageLogger^ logger = nullptr;
		int countOfTests = 0;
	public:
		static String^ executorUriString = gcnew String("executor://darknessNight_CppUnitTestExecutor/v1");
		static Uri^ executorUri = gcnew Uri(executorUriString);
	public:
		virtual void DiscoverTests(IEnumerable<String ^> ^sources, IDiscoveryContext ^discoveryContext,
								   IMessageLogger ^messLogger, ITestCaseDiscoverySink ^discoverySink);
		List<ObjectModel::TestCase^>^ getTests(IEnumerable<String ^> ^sources, IDiscoveryContext ^discoveryContext,
											   IMessageLogger ^messLogger, ITestCaseDiscoverySink ^discoverySink);
	private:
		void logEndFindTest();
		void prepareToFindTests(Microsoft::VisualStudio::TestPlatform::ObjectModel::Logging::IMessageLogger ^ messLogger);
		List<ObjectModel::TestCase^>^ findAllTests(IEnumerable<System::String ^> ^ sources, ITestCaseDiscoverySink ^discoverySink);
		void searchTestsInFile(System::String ^ &path, Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter::ITestCaseDiscoverySink ^ discoverySink, System::Collections::Generic::List<Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase ^> ^ cases);
		darknessNight::TestsRunner::TestDiscover getNativeDiscover();
		void freeLoadedLibraries(darknessNight::TestsRunner::TestDiscover &discover);
		void readTestsFromFile(System::String ^& path, darknessNight::TestsRunner::TestDiscover &discover);
		void saveTestsAsTestCases(darknessNight::TestsRunner::TestDiscover &discover, System::String ^& path, Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter::ITestCaseDiscoverySink ^ discoverySink, System::Collections::Generic::List<Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase ^> ^ cases);
		void saveAndSendTestCase(darknessNight::CppUnitTestFramework::TestCasePtr &test, System::String ^& path, Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter::ITestCaseDiscoverySink ^ discoverySink, System::Collections::Generic::List<Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase ^> ^ cases);
	};
}
