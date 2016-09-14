#include "stdafx.h"
#include "TestReportConverter.h"
#include "TestsExecutor.h"

ObjectModel::TestCase ^ darknessNight::CppUnitTest::VSAdapter::TestReportConverter::getVSTestCaseFromReport(TestReport & report, System::String ^ source) {
	auto fullName = report.getSuiteName() + "::" + report.getTestName();
	auto testCase = gcnew ObjectModel::TestCase(ConvertTools::CppStringToCliString(fullName), TestsExecutor::myUri, source);
	testCase->CodeFilePath = ConvertTools::CppStringToCliString(report.getFile());
	testCase->DisplayName = ConvertTools::CppStringToCliString(report.getTestName());
	testCase->LineNumber = report.getLine();
	testCase->Id = Guid();
	testCase->Traits->Add(gcnew ObjectModel::Trait("Category", ConvertTools::CppStringToCliString(report.getCategory().getFullName())));
	testCase->SetPropertyValue(ObjectModel::TestResultProperties::Outcome, TestOutcome::Passed);
	return testCase;
}

ObjectModel::TestResult ^ darknessNight::CppUnitTest::VSAdapter::TestReportConverter::getVSResultFromReport(TestReport & report, System::String ^ source) {
	auto testResult = getVSResult(report, source);
	setResultProperties(report, testResult);
	return testResult;
}

ObjectModel::TestResult ^ darknessNight::CppUnitTest::VSAdapter::TestReportConverter::getVSResult(darknessNight::CppUnitTestFramework::TestReport & report, System::String ^ source) {
	auto testCase = getVSTestCaseFromReport(report, source);
	return gcnew ObjectModel::TestResult(testCase);
}

void darknessNight::CppUnitTest::VSAdapter::TestReportConverter::setResultProperties(darknessNight::CppUnitTestFramework::TestReport & report, Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult) {
	setResultOutcome(report, testResult);
	setResultDuration(testResult, report);
	setResultMessage(testResult, report);
	setMachineName(testResult);
}

void darknessNight::CppUnitTest::VSAdapter::TestReportConverter::setMachineName(Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult) {
	testResult->ComputerName = Environment::MachineName;
}

void darknessNight::CppUnitTest::VSAdapter::TestReportConverter::setResultMessage(Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult, darknessNight::CppUnitTestFramework::TestReport & report) {
	testResult->ErrorMessage = ConvertTools::CppStringToCliString(report.getResult().getFullMessage());
}

void darknessNight::CppUnitTest::VSAdapter::TestReportConverter::setResultDuration(Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult, darknessNight::CppUnitTestFramework::TestReport & report) {
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(report.getResult().getDurationTime()).count()/1000.0*System::TimeSpan::TicksPerMillisecond;
	testResult->Duration = System::TimeSpan::FromTicks(time <= 0 ? 1 : time);
	testResult->StartTime = ConvertTools::ChronoTimePointToDateTimeOffset(report.getResult().getStartTime());
	testResult->EndTime = ConvertTools::ChronoTimePointToDateTimeOffset(report.getResult().getEndTime());
}

void darknessNight::CppUnitTest::VSAdapter::TestReportConverter::setResultOutcome(darknessNight::CppUnitTestFramework::TestReport & report, Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult) {
	if (report.getResult().getCause() == "Success")
		testResult->Outcome = ObjectModel::TestOutcome::Passed;
	else if (report.getResult().getCause() == "Ignored")
		testResult->Outcome = ObjectModel::TestOutcome::Skipped;
	else
		testResult->Outcome = ObjectModel::TestOutcome::Failed;
}
