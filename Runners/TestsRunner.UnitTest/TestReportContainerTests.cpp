#include "stdafx.h"
#include "../TestsRunner/TestReportContainer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {namespace TestsRunner {namespace Tests{
	class FakeTestReport :public TestReport {
	public:
		FakeTestReport(std::string name) {
			this->testName = name;
		}

		FakeTestReport(std::string name, int time) {
			this->testName = name;
			this->testResult.setTime(std::chrono::nanoseconds(time));
		}

		FakeTestReport(std::string name, TestCategory cat) {
			this->testName = name;
			this->testCategory = cat;
		}

		FakeTestReport(std::string name, std::string suite) {
			this->testName = name;
			this->testSuite = suite;
		}

		FakeTestReport(std::string name, bool isPassing) {
			this->testName = name;
			this->testResult = TestResult(isPassing);
		}
	};

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
			container.addReports({ FakeTestReport("Test1",true),FakeTestReport("Test2",false) });
			auto reports = container.getReportsGroupBySuite();
			Assert::AreEqual<std::string>("Test2", reports["Fail"][0].getTestName());
			Assert::AreEqual<std::string>("Test1", reports["Success"][0].getTestName());
			Assert::AreEqual<std::string>("Test3", reports["Ignore"][0].getTestName());
		}
	};
}}}