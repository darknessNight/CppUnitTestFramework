#pragma once
#include <TestsRunner/TestExecutor.h>
#include "MessageLogger.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestPlatform;
using namespace Microsoft::VisualStudio::TestPlatform::ObjectModel;
using namespace Microsoft::VisualStudio::TestPlatform::ObjectModel::Adapter;
using namespace Microsoft::VisualStudio::TestPlatform::ObjectModel::Logging;

namespace darknessNight::CppUnitTest::VSAdapter {
	[ExtensionUri(gcnew String("executor://darknessNight_CppUnitTestExecutor/v1"))]
	public ref class TestsExecutor: public ITestExecutor{
	private:
		MessageLogger^ logger = nullptr;
		bool m_cancelled;
	public:

		// Inherited via ITestExecutor
		virtual void RunTests(IEnumerable<ObjectModel::TestCase ^> ^tests, IRunContext ^runContext, IFrameworkHandle ^frameworkHandle){
			logger = gcnew MessageLogger(frameworkHandle);
			m_cancelled = false;

			for each(auto test in tests) {
				if (m_cancelled) break;

				
				auto testResult = gcnew ObjectModel::TestResult(test);

				testResult->Outcome = TestOutcome::Skipped;
				frameworkHandle->RecordResult(testResult);
			}

		}
		virtual void RunTests(IEnumerable<String ^> ^sources, IRunContext ^runContext, IFrameworkHandle ^frameworkHandle){}
		virtual void Cancel(){
			m_cancelled = true;
		}
	};
}