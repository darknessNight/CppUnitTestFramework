#pragma once
#include <vector>
#include <msclr\marshal_cppstd.h>
#include <TestsRunner/TestsDiscover.h>
#include "MessageLogger.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Xml;
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
		String^ executorUriString = gcnew String("executor://darknessNight_CppUnitTestExecutor/v1");
		Uri^ executorUri = gcnew Uri(executorUriString);
	public:
		TestDiscover() {
			darknessNight::DependencyContainer::DIContainer::Register<darknessNight::SharedLibrary::DynamicLibrary, darknessNight::SharedLibrary::DynamicLibrary>();
			darknessNight::DependencyContainer::DIContainer::Register<darknessNight::Filesystem::Directory>(std::make_shared<darknessNight::Filesystem::Directory>("."));
		}

		virtual void DiscoverTests(IEnumerable<String ^> ^sources, IDiscoveryContext ^discoveryContext,
								   IMessageLogger ^messLogger, ITestCaseDiscoverySink ^discoverySink) {
			getTests(sources, discoveryContext, messLogger, discoverySink);
		}
	
		List<ObjectModel::TestCase^>^ getTests(IEnumerable<String ^> ^sources, IDiscoveryContext ^discoveryContext,
					  IMessageLogger ^messLogger, ITestCaseDiscoverySink ^discoverySink) {
			prepareToFindTests(messLogger);
			auto cases = findAllTests(sources, discoverySink);
			logEndFindTest();
			return cases;
		}

		void logEndFindTest() {
			logger->sendInfo("Tests found: " + countOfTests.ToString());
			logger->sendInfo("----CppUnitTestAdapter:Ended----");
		}

		void prepareToFindTests(Microsoft::VisualStudio::TestPlatform::ObjectModel::Logging::IMessageLogger ^ messLogger) {
			logger = gcnew MessageLogger(messLogger);
			countOfTests = 0;
			logger->sendInfo("----CppUnitTestAdapter:Started----");
		}


	private:
		List<ObjectModel::TestCase^>^ findAllTests(IEnumerable<System::String ^> ^ sources, ITestCaseDiscoverySink ^discoverySink) {
			List<ObjectModel::TestCase^>^ cases = gcnew List<ObjectModel::TestCase^>();
			for each (auto path in sources) {
				searchTestsInFile(path, discoverySink, cases);
			}
			return cases;
		}

		void searchTestsInFile(System::String ^ &path, Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter::ITestCaseDiscoverySink ^ discoverySink, System::Collections::Generic::List<Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase ^> ^ cases) {
			darknessNight::TestsRunner::TestsDiscover discover;
			readTestsFromFile(path, discover);
			saveTestsAsTestCases(discover, path, discoverySink, cases);
		}

		void readTestsFromFile(System::String ^& path, darknessNight::TestsRunner::TestsDiscover &discover) {
			logger->sendInfo("Has: " + path);
			discover.findInFile(msclr::interop::marshal_as<std::string>(path));
		}

		void saveTestsAsTestCases(darknessNight::TestsRunner::TestsDiscover &discover, System::String ^& path, Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter::ITestCaseDiscoverySink ^ discoverySink, System::Collections::Generic::List<Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase ^> ^ cases) {
			for (auto test : discover.getTestsList()) {
				saveAndSendTestCase(test, path, discoverySink, cases);
				countOfTests++;
			}
		}

		void saveAndSendTestCase(darknessNight::CppUnitTestFramework::TestCasePtr &test, System::String ^& path, Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter::ITestCaseDiscoverySink ^ discoverySink, System::Collections::Generic::List<Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase ^> ^ cases) {
			ObjectModel::TestCase^ testCase = gcnew ObjectModel::TestCase(gcnew String(test->getName().c_str()), executorUri, path);
			discoverySink->SendTestCase(testCase);
			cases->Add(testCase);
		}
	
		System::String^ getCliString(std::string str) {
			return gcnew System::String(str.c_str());
		}
	};

}