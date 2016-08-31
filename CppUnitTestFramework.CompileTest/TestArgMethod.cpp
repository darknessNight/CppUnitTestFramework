#include "CppUnitTestFramework.CompileTest.h"
#include "TestArgMethod.h"
using namespace darknessNight::CppUnitTestFramework;

void testArgMethodAndFunc() {
	int count = 0;
	std::string samplename;
	auto testCases = getTestCasesList();
	count = findArgMethods(testCases, samplename);
	checkHasCorrectArgMethodCount(count);
	checkHasCorrectArgMethodName(samplename);
}

void checkHasCorrectArgMethodName(std::string &samplename)
{
	if (noHasArgsInName(samplename))
		throw SpecialException("ArgMethod no have args in name");
}

bool noHasArgsInName(std::string & samplename)
{
	int openPos = samplename.find("(");
	int closePos = samplename.find(")");
	return openPos < 0 || closePos < 0 || closePos - openPos <= 1;
}

void checkHasCorrectArgMethodCount(int count)
{
	if (count != countOfArgMethods)
		throw SpecialException("Not found all ArgMethods");
}

int findArgMethods(std::vector<std::string> &testCases, std::string &samplename)
{
	int count = 0;
	for (auto test = testCases.begin(); test != testCases.end(); test++) {
		checkArgMethodName(*test, count, samplename);
	}
	return count;
}

void checkArgMethodName(std::string test, int & count, std::string & samplename)
{
	int pos = test.find("ArgMethod");
	if (pos >= 0) {
		count++;
		samplename = test;
	}
}

const std::vector<std::string> getTestCasesList()
{
	auto suite = TestsCollectionExport::getTestContainer().getTestSuiteByName(getClassName<TestSuiteTestMacro>());
	auto testCases = suite->getTestCaseList();
	return testCases;
}
