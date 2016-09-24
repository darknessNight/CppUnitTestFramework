#include "TestReportContainer.h"

void darknessNight::TestsRunner::TestReportContainer::addReports(std::initializer_list<TestReport> reports) {
	for (auto report : reports)
		reportsArray.push_back(report);
}

std::vector<TestReport> darknessNight::TestsRunner::TestReportContainer::getReportsSortByName() {
	sort(reportsArray.begin(), reportsArray.end(), &TestReportContainer::sortByName);
	return reportsArray;
}

bool darknessNight::TestsRunner::TestReportContainer::sortByName(TestReport & report1, TestReport & report2) {
	return report1.getFullName() < report2.getFullName();
}

std::vector<TestReport> darknessNight::TestsRunner::TestReportContainer::getReportsSortByTime() {
	sort(reportsArray.begin(), reportsArray.end(), &TestReportContainer::sortByTime);
	return reportsArray;
}

bool darknessNight::TestsRunner::TestReportContainer::sortByTime(TestReport & report1, TestReport & report2) {
	return report1.getResult().getDurationTime() < report2.getResult().getDurationTime();
}

darknessNight::TestsRunner::CategoryContainer darknessNight::TestsRunner::TestReportContainer::getReportsGroupByCategory() {
	CategoryContainer ret;
	for (auto test : reportsArray)
		ret.addReportToCat(test);
	return ret;
}

std::map<std::string, std::vector<TestReport>> darknessNight::TestsRunner::TestReportContainer::getReportsGroupByResult() {
	return groupBy<std::string, TestReport>(reportsArray, TestReportInfoExtract::getResult);
}

std::map<std::string, std::vector<TestReport>> darknessNight::TestsRunner::TestReportContainer::getReportsGroupByDuration(std::initializer_list<int> groupsList) {
	return groupBy<std::string, TestReport>(reportsArray, [&](TestReport& report) {return TestReportInfoExtract::getDurationGroupIndex(report, groupsList); });
}

std::map<std::string, std::vector<TestReport>> darknessNight::TestsRunner::TestReportContainer::getReportsGroupBySuite() {
	return groupBy<std::string, TestReport>(reportsArray, [](TestReport& report) {return report.getSuiteName(); });
}
