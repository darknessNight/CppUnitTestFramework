#include "stdafx.h"
#include "TestReportConverter.h"
#include "TestsExecutor.h"

using namespace darknessNight::CppUnitTest::VSAdapter;

ObjectModel::TestCase ^ TestReportConverter::getVSTestCaseFromReport(TestReport & report, System::String ^ source) {
	auto testCase = getVSTestCaseWithBasicData(report, source);
	testCase = setTestCaseAdditionalData(testCase, report);
	return testCase;
}

ObjectModel::TestCase ^ TestReportConverter::setTestCaseAdditionalData(ObjectModel::TestCase ^ testCase, darknessNight::CppUnitTestFramework::TestReport & report) {
	testCase = setTestPos(testCase, report);
	testCase = setTestVisibleName(testCase, report);
	testCase = setTestCategory(testCase, report);
	return testCase;
}

ObjectModel::TestCase ^ TestReportConverter::getVSTestCaseWithBasicData(darknessNight::CppUnitTestFramework::TestReport & report, System::String ^ source) {
	auto fullName = report.getSuiteName() + "::" + report.getTestName();
	auto testCase = gcnew ObjectModel::TestCase(ConvertTools::CppStringToCliString(fullName), TestExecutor::myUri, source);
	testCase->SetPropertyValue(ObjectModel::TestResultProperties::Outcome, TestOutcome::None);
	return testCase;
}

ObjectModel::TestCase ^ TestReportConverter::setTestCategory(ObjectModel::TestCase ^ testCase, darknessNight::CppUnitTestFramework::TestReport & report) {
	testCase->Traits->Add(gcnew ObjectModel::Trait("Category", ConvertTools::CppStringToCliString(report.getCategory().getFullName())));
	return testCase;
}

ObjectModel::TestCase ^ TestReportConverter::setTestVisibleName(ObjectModel::TestCase ^ testCase, darknessNight::CppUnitTestFramework::TestReport & report) {
	testCase->DisplayName = ConvertTools::CppStringToCliString(report.getTestName());
	return testCase;
}

ObjectModel::TestCase ^ TestReportConverter::setTestPos(ObjectModel::TestCase ^ testCase, darknessNight::CppUnitTestFramework::TestReport & report) {
	testCase->CodeFilePath = ConvertTools::CppStringToCliString(report.getFile());
	testCase->LineNumber = report.getLine();
	return testCase;
}

ObjectModel::TestResult ^ TestReportConverter::getVSResultFromReport(TestReport & report, System::String ^ source) {
	auto testResult = getVSResult(report, source);
	testResult = setResultProperties(report, testResult);
	return testResult;
}

ObjectModel::TestResult ^ TestReportConverter::getVSResult(darknessNight::CppUnitTestFramework::TestReport & report, System::String ^ source) {
	auto testCase = getVSTestCaseFromReport(report, source);
	return gcnew ObjectModel::TestResult(testCase);
}

ObjectModel::TestResult ^ TestReportConverter::setResultProperties(darknessNight::CppUnitTestFramework::TestReport & report, ObjectModel::TestResult ^ testResult) {
	testResult = setResultOutcome(report, testResult);
	testResult = setResultDuration(testResult, report);
	testResult = setResultMessage(testResult, report);
	testResult = setMachineName(testResult);
	return testResult;
}

ObjectModel::TestResult ^ TestReportConverter::setMachineName(ObjectModel::TestResult ^ testResult) {
	testResult->ComputerName = Environment::MachineName;
	return testResult;
}

ObjectModel::TestResult^ TestReportConverter::setResultMessage(ObjectModel::TestResult ^ testResult, darknessNight::CppUnitTestFramework::TestReport & report) {
	testResult->ErrorMessage = ConvertTools::CppStringToCliString(report.getResult().getFullMessage());
	return testResult;
}

ObjectModel::TestResult^ TestReportConverter::setResultDuration(ObjectModel::TestResult ^ testResult, darknessNight::CppUnitTestFramework::TestReport & report) {
	testResult->Duration = ConvertTools::ChronoDurationToTimeSpan(report.getResult().getDurationTime());
	testResult->StartTime = ConvertTools::ChronoTimePointToDateTimeOffset(report.getResult().getStartTime());
	testResult->EndTime = ConvertTools::ChronoTimePointToDateTimeOffset(report.getResult().getEndTime());
	return testResult;
}

ObjectModel::TestResult^ TestReportConverter::setResultOutcome(darknessNight::CppUnitTestFramework::TestReport & report, ObjectModel::TestResult ^ testResult) {
	if (report.getResult().getCause() == "Success")
		testResult->Outcome = ObjectModel::TestOutcome::Passed;
	else if (report.getResult().getCause() == "Ignored")
		testResult->Outcome = ObjectModel::TestOutcome::Skipped;
	else
		testResult->Outcome = ObjectModel::TestOutcome::Failed;
	return testResult;
}
