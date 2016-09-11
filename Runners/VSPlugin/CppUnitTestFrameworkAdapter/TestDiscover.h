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
	public:

		virtual void DiscoverTests(IEnumerable<String ^> ^sources, IDiscoveryContext ^discoveryContext,
								   IMessageLogger ^messLogger, ITestCaseDiscoverySink ^discoverySink) {
			logger = gcnew MessageLogger(messLogger);
			logger->sendInfo("----CppUnitTestAdapter:Started----");
			findAllTests(sources);
			logger->sendInfo("----CppUnitTestAdapter:Ended----");
		}

		void findAllTests(System::Collections::Generic::IEnumerable<System::String ^> ^ sources) {
			for each (auto path in sources)
				logger->sendInfo("Has: " + path);
		}
	};

}