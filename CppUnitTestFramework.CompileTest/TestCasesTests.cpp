#include "TestCasesTests.h"

using namespace darknessNight_CppUnitTestFramework;

void testClassAndMethodMacro()
{
	std::string name = getClassName<TestSuiteTestMacro>();
	testTestCaseMacro(testCaseCount, name, "FirstTestMethod", macrosFile, testMethodLine);
}

void testFunctionMacro() {
	testTestCaseMacro(1, "Unnamed", "TestFunctionTest", macrosFile, testFuncLine);
}

void testTestCaseMacro(int testCaseCount, std::string suite, std::string funcName, std::string file, int funcLine)
{
	checkTestSuiteHasMethod(testCaseCount, suite, funcName);
	checkCorrectRemeberFileAndLine(suite, funcName, file, funcLine);
}

void checkCorrectRemeberFileAndLine(std::string &suite, std::string &funcName, std::string &file, int funcLine)
{
	TestReport report = getTestRaport(suite, funcName);
	checkCorrectRemeberFile(report, file);
	checkCorrectRememberLine(report, funcLine);
}

const darknessNight_CppUnitTestFramework::TestReport getTestRaport(std::string & suite, std::string & funcName)
{
	TestSuitePtr testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName(suite);
	return testSuite->runTestAndGetReport(funcName);
}

void checkCorrectRememberLine(darknessNight_CppUnitTestFramework::TestReport report, int funcLine)
{
	if (report.getLine() != funcLine)
		throw SpecialException("No saved correct test line. Current saved line: " + std::to_string(report.getLine()));
}

void checkCorrectRemeberFile(darknessNight_CppUnitTestFramework::TestReport report, std::string & file)
{
	if (report.getFile() != file)
		throw SpecialException("No saved correct test file. Current saved file: " + report.getFile());
}

void checkTestSuiteHasMethod(int testCaseCount, std::string &suite, std::string &funcName)
{
	std::vector<std::string> testCases = getTestCaseListFromSuite(suite);
	if (testCases.size() < testCaseCount)
		throw SpecialException("No have func in \"" + suite + "\" TestSuite");
	if (!findMethod(testCases, funcName))
		throw SpecialException("No have \"" + funcName + "\" in testSuite");
}

bool findMethod(std::vector<std::string> &testCases, std::string &funcName)
{
	bool found = false;
	for (auto test = testCases.begin(); test != testCases.end(); test++)
		if (*test == funcName)
			found = true;
	return found;
}

std::vector<std::string> getTestCaseListFromSuite(std::string &suite)
{
	TestContainer& container = TestsCollectionExport::getTestContainer();
	TestSuitePtr testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName(suite);
	return testSuite->getTestCaseList();
}
