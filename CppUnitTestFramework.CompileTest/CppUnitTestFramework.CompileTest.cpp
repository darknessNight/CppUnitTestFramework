// CppUnitTestFramework.CompileTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <CppUnitTestsFramework\Framework.h>
#include <iostream>
#include "CppUnitTestFramework.CompileTest.h"

using namespace darknessNight::CppUnitTestFramework;
using namespace std;

int testMethodLine = __LINE__ + 2;
TEST_CLASS(TestSuiteTestMacro) {
	TEST_METHOD(FirstTestMethod) {
		throw exception();
	}
};

int testFuncLine = __LINE__ + 1;
TEST_FUNCTION(TestFunctionTest) {

}

class SpecialException {
private:
	string message;
public:
	SpecialException(string mess) {
		message = mess;
	}

	string what() {
		return message;
	}
};

void drawLineTest() {
	cout << "\n===========================================================================\n\n";
}
void drawLineHeader() {
	cout << "\n---------------------------------------------------------------------------\n";
}

int main()
{
	cout << "TestClass tests:";
	drawLineHeader();
	showError(testClassAndMethodMacro);
	drawLineTest();
	cout << "TestFunction tests:";
	drawLineHeader();
	showError(testFunctionMacro);
	drawLineTest();
	system("pause");
	return 0;
}

void testClassAndMethodMacro()
{
	string name = typeid(TestSuiteTestMacro).name();
	name = name.substr(strlen("class "));
	testTestCaseMacro(name, "FirstTestMethod", testMethodLine);
}

void testFunctionMacro() {
	testTestCaseMacro("Unnamed", "TestFunctionTest", testFuncLine);
}

void testTestCaseMacro(string suite, string funcName, int funcLine)
{
	TestContainer& container = TestsCollectionExport::getTestContainer();
	TestSuitePtr testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName(suite);
	std::vector<string> testCases = testSuite->getTestCaseList();
	if (testCases.size() != 1)
		throw SpecialException("No have func in \""+suite+"\" TestSuite");
	if (testCases[0] != funcName)
		throw SpecialException("No have \""+funcName+"\" in testSuite");
	TestReport report = testSuite->runTestAndGetReport(funcName);
	if (report.getFile() != __FILE__)
		throw SpecialException("No saved correct test file. Current saved file: " + report.getFile());
	if (report.getLine() != funcLine)
		throw SpecialException("No saved correct test line. Current saved line: " + to_string(report.getLine()));
	cout << "Success" << "\n";
}

void showError(void(*func)()) {
	try {
		func();
	}
	catch (SpecialException ex) {
		cout << ex.what() << "\n";
	}
	catch (NotFoundException ex) {
		cout << "Not register test class\n";
		cout << "Exception message: " << ex.what()<<"\n";
	}
	catch (TestRegisterException ex) {
		cout << "Register method exception\n";
		cout << "Exception message: " << ex.what() << "\n";
	}
	catch (exception ex) {
		cout << "Catched exception: " << ex.what() << "\n";
	}
	catch (...) {
		cout << "Unknow error" << "\n";
	}
}

