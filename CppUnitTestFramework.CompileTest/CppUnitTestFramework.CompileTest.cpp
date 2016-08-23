// CppUnitTestFramework.CompileTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <CppUnitTestsFramework\Framework.h>
#include <iostream>
#include "CppUnitTestFramework.CompileTest.h"

using namespace darknessNight::CppUnitTestFramework;
using namespace std;

TEST_CLASS(TestSuiteTestMacro) {
	TEST_METHOD(FirstTestMethod) {
		throw exception();
	}
};


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
	TestSuitePtr testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName("TestSuiteTestMacro");
	std::vector<string> testCases = testSuite->getTestCaseList();
	if (testCases.size() != 1)
		throw SpecialException("No have method in testSuite");
	if (testCases[0] != "FirstTestMethod")
		throw SpecialException("No have method with correct name in testSuite");
	cout << "Success" << "\n";
}

void testFunctionMacro()
{
	TestSuitePtr testSuite = TestsCollectionExport::getTestContainer().getTestSuiteByName("Unnamed");
	std::vector<string> testCases = testSuite->getTestCaseList();
	if (testCases.size() != 1)
		throw SpecialException("No have func in unnamed TestSuite");
	if (testCases[0] != "TestFunctionTest")
		throw SpecialException("No have func with correct name");
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
	catch (exception ex) {
		cout << "Catched exception: " << ex.what() << "\n";
	}
	catch (...) {
		cout << "Unknow error" << "\n";
	}
}

