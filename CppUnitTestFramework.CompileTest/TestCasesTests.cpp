#include "CppUnitTestFramework.CompileTest.h"
#include <iostream>
#include <CppUnitTestsFramework\Framework.h>

using namespace darknessNight::CppUnitTestFramework;
using namespace std;

void testTestCaseMacro(string suite, string funcName, string file, int funcLine)
{
	TestContainer& container = TestsCollectionExport::getTestContainer();
	TestSuitePtr testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName(suite);
	std::vector<string> testCases = testSuite->getTestCaseList();
	if (testCases.size() != 1)
		throw SpecialException("No have func in \"" + suite + "\" TestSuite");
	if (testCases[0] != funcName)
		throw SpecialException("No have \"" + funcName + "\" in testSuite");
	TestReport report = testSuite->runTestAndGetReport(funcName);
	if (report.getFile() != file)
		throw SpecialException("No saved correct test file. Current saved file: " + report.getFile());
	if (report.getLine() != funcLine)
		throw SpecialException("No saved correct test line. Current saved line: " + to_string(report.getLine()));
	cout << "Success" << "\n";
}