#include "TestReportInfoExtractor.h"

std::string darknessNight::TestsRunner::TestReportInfoExtract::getResult(TestReport & test) {
	if (test.getResult().isSuccess())
		return "Success";
	else if (test.getResult().getCause() == "Ignored")
		return "Ignored";
	else return "Failed";
}

std::string darknessNight::TestsRunner::TestReportInfoExtract::getDurationGroupIndex(TestReport & report, std::initializer_list<int>& groupsList) {
	int group;
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(report.getResult().getDurationTime()).count();
	auto overGroup = findDurationGroup(group, time, groupsList);
	return getGroupIndexString(overGroup, group);
}

bool darknessNight::TestsRunner::TestReportInfoExtract::findDurationGroup(int & group, long long & time, std::initializer_list<int>& groupsList) {
	for (auto it = groupsList.begin(); it != groupsList.end(); it++) {
		group = *it;
		if (time < group) {
			return true;
		}
	}
	return false;
}

std::string darknessNight::TestsRunner::TestReportInfoExtract::getGroupIndexString(bool overGroup, int & group) {
	if (overGroup)
		return "<" + std::to_string(group);
	else
		return ">=" + std::to_string(group);
}
