#include "stdafx.h"
#include <CppUnitTestFramework/PredefinedTestResults.h>
#include "../TestsRunner/TestReportContainer.h"
#include "FakeTestReport.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {namespace TestsRunner {namespace Tests{

	TEST_CLASS(TestReportSortTests)
	{
	public:
		TEST_METHOD(GetReportsSortByName_HasTwoRaports_CheckReturnRaportsInCorrectOrder)
		{
			TestReportContainer container;
			container.addReports({ FakeTestReport("Test2"),FakeTestReport("Test1") });
			auto reports = container.getReportsSortByName();
			Assert::AreEqual<std::string>("Test1", reports[0].getTestName());
			Assert::AreEqual<std::string>("Test2", reports[1].getTestName());
		}

		TEST_METHOD(GetReportsSortByTime_HasTwoRaports_CheckReturnRaportsInCorrectOrder) {
			TestReportContainer container;
			container.addReports({ FakeTestReport("Test1",20),FakeTestReport("Test2",10) });
			auto reports = container.getReportsSortByTime();
			Assert::AreEqual<std::string>("Test2", reports[0].getTestName());
			Assert::AreEqual<std::string>("Test1", reports[1].getTestName());
		}

		TEST_METHOD(GetReportsGroupByCategory_HasTwoRaports_CheckReturnRaportsInCorrectOrder) {
			TestReportContainer container;
			container.addReports({ FakeTestReport("Test1",TestCategory("Cat1.SubCat")),FakeTestReport("Test2",TestCategory("Cat2")) });
			auto reports = container.getReportsGroupByCategory();
			Assert::AreEqual<std::string>("Test2", reports["Cat2"][0].getTestName());
			Assert::AreEqual<std::string>("Test1", reports["Cat1"]["SubCat"][0].getTestName());
		}

		TEST_METHOD(GetReportsGroupByTestResult_HasTwoRaports_CheckReturnRaportsInCorrectOrder) {
			TestReportContainer container;
			container.addReports({ FakeTestReport("Test1",SuccessTestResult()),FakeTestReport("Test2",TestResult(false)),
			FakeTestReport("Test3", IgnoredTestResult("Ignored"))});
			auto reports = container.getReportsGroupBySuite();
			Assert::AreEqual<std::string>("Test2", reports["Failed"][0].getTestName());
			Assert::AreEqual<std::string>("Test1", reports["Success"][0].getTestName());
			Assert::AreEqual<std::string>("Test3", reports["Ignored"][0].getTestName());
		}
	};
}}}