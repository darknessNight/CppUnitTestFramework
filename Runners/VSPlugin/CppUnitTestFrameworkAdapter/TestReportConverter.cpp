#include "stdafx.h"
#include "TestReportConverter.h"
#include "TestsExecutor.h"

ObjectModel::TestCase ^ darknessNight::CppUnitTest::VSAdapter::TestReportConverter::getVSTestCaseFromReport(TestReport & report, System::String ^ source) {
	auto testCase = gcnew ObjectModel::TestCase(ConvertTools::CppStringToCliString(report.getFullName()), TestsExecutor::myUri, source);
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
	testResult->ComputerName = Environment::MachineName;
}

void darknessNight::CppUnitTest::VSAdapter::TestReportConverter::setResultMessage(Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult, darknessNight::CppUnitTestFramework::TestReport & report) {
	testResult->ErrorMessage = ConvertTools::CppStringToCliString(report.getResult().getFullMessage());
}

void darknessNight::CppUnitTest::VSAdapter::TestReportConverter::setResultDuration(Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult, darknessNight::CppUnitTestFramework::TestReport & report) {
	testResult->Duration = System::TimeSpan::FromMilliseconds(std::chrono::duration_cast<std::chrono::milliseconds>(report.getResult().getDurationTime()).count());
}

void darknessNight::CppUnitTest::VSAdapter::TestReportConverter::setResultOutcome(darknessNight::CppUnitTestFramework::TestReport & report, Microsoft::VisualStudio::TestPlatform::ObjectModel::TestResult ^ testResult) {
	if (report.getResult().getCause() == "Success")
		testResult->Outcome = ObjectModel::TestOutcome::Passed;
	else if (report.getResult().getCause() == "Ignored")
		testResult->Outcome = ObjectModel::TestOutcome::Skipped;
	else
		testResult->Outcome = ObjectModel::TestOutcome::Failed;
}
