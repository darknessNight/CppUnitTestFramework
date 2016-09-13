#pragma once
#include <CppUnitTestFramework/TestReport.h>
#include <chrono>
#include "ConvertTools.h"

using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestPlatform;
using namespace darknessNight::CppUnitTestFramework;

namespace darknessNight::CppUnitTest::VSAdapter {
	ref class TestReportConverter {
	public:
		static ObjectModel::TestCase^ getVSTestCaseFromReport(TestReport& report, System::String^ source);
		static ObjectModel::TestResult^ getVSResultFromReport(TestReport& report, System::String^ source);
	private:
		static ObjectModel::TestResult^ getVSResult(darknessNight::CppUnitTestFramework::TestReport & report, System::String ^ source);
		static void setResultProperties(darknessNight::CppUnitTestFramework::TestReport & report, Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult);
		static void setResultMessage(Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult, darknessNight::CppUnitTestFramework::TestReport & report);
		static void setResultDuration(Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult, darknessNight::CppUnitTestFramework::TestReport & report);
		static void setResultOutcome(darknessNight::CppUnitTestFramework::TestReport & report, Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult);
	};
}