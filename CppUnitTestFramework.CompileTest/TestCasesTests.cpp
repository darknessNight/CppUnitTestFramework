#include "TestCasesTests.h"

using namespace darknessNight::CppUnitTestFramework;
using namespace std;

void testTestCaseMacro(string suite, string funcName, string file, int funcLine)
{
	checkTestSuiteHasMethod(suite, funcName);
	checkCorrectRemeberFileAndLine(suite, funcName, file, funcLine);
	cout << "Success" << "\n";
}

void checkCorrectRemeberFileAndLine(std::string &suite, std::string &funcName, std::string &file, int funcLine)
{
	TestReport report = getTestRaport(suite, funcName);
	checkCorrectRemeberFile(report, file);
	checkCorrectRememberLine(report, funcLine);
}

const darknessNight::CppUnitTestFramework::TestReport getTestRaport(std::string & suite, std::string & funcName)
{
	TestSuitePtr testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName(suite);
	return testSuite->runTestAndGetReport(funcName);
}

void checkCorrectRememberLine(darknessNight::CppUnitTestFramework::TestReport report, int funcLine)
{
	if (report.getLine() != funcLine)
		throw SpecialException("No saved correct test line. Current saved line: " + to_string(report.getLine()));
}

void checkCorrectRemeberFile(darknessNight::CppUnitTestFramework::TestReport report, std::string & file)
{
	if (report.getFile() != file)
		throw SpecialException("No saved correct test file. Current saved file: " + report.getFile());
}

void checkTestSuiteHasMethod(std::string &suite, std::string &funcName)
{
	int testCaseCount = 1;
	std::vector<string> testCases = getTestCaseListFromSuite(suite);
	if (testCases.size() != testCaseCount)
		throw SpecialException("No have func in \"" + suite + "\" TestSuite");
	if (testCases[0] != funcName)
		throw SpecialException("No have \"" + funcName + "\" in testSuite");
}

std::vector<string> getTestCaseListFromSuite(std::string &suite)
{
	TestContainer& container = TestsCollectionExport::getTestContainer();
	TestSuitePtr testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName(suite);
	return testSuite->getTestCaseList();
}
