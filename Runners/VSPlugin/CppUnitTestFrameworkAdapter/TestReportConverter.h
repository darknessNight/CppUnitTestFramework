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
		static ObjectModel::TestCase^ setTestCaseAdditionalData(Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase ^ testCase, darknessNight::CppUnitTestFramework::TestReport & report);
		static ObjectModel::TestCase^ getVSTestCaseWithBasicData(darknessNight::CppUnitTestFramework::TestReport & report, System::String ^ source);
		static ObjectModel::TestCase^ setTestCategory(Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase ^ testCase, darknessNight::CppUnitTestFramework::TestReport & report);
		static ObjectModel::TestCase^ setTestVisibleName(Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase ^ testCase, darknessNight::CppUnitTestFramework::TestReport & report);
		static ObjectModel::TestCase^ setTestPos(Microsoft::VisualStudio::TestPlatform::ObjectModel::TestCase ^ testCase, darknessNight::CppUnitTestFramework::TestReport & report);
		static ObjectModel::TestResult^ getVSResult(darknessNight::CppUnitTestFramework::TestReport & report, System::String ^ source);
		static ObjectModel::TestResult^ setResultProperties(darknessNight::CppUnitTestFramework::TestReport & report, Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult);
		static ObjectModel::TestResult^ setMachineName(Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult);
		static ObjectModel::TestResult^ setResultMessage(Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult, darknessNight::CppUnitTestFramework::TestReport & report);
		static ObjectModel::TestResult^ setResultDuration(Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult, darknessNight::CppUnitTestFramework::TestReport & report);
		static ObjectModel::TestResult^ setResultOutcome(darknessNight::CppUnitTestFramework::TestReport & report, Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult);
	};
}