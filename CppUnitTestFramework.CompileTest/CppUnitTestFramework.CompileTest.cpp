// CppUnitTestFramework.CompileTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <CppUnitTestsFramework\Framework.h>
#include <iostream>
#include "CppUnitTestFramework.CompileTest.h"


using namespace std;
using namespace darknessNight::CppUnitTestFramework;


TEST_SUITE(SAME_SUITE)
TEST_SUITE_WITH_CATEGORY(SecondSuite, "Category")


TEST_CLASS_WITH_CATEGORY(TestSuiteClassOne, "Category") {
};

int testMethodLine = __LINE__ + 2;
TEST_CLASS(TestSuiteTestMacro) {
	TEST_METHOD(FirstTestMethod) {
		//throw exception();
	}

public:
	static bool collapseSetup;
	static bool collapseTearDown;

	SETUP_METHOD(SetUp) {
		if (collapseSetup)
			throw exception();
	}

	TEARDOWN_METHOD(TearDown) {
		if (collapseTearDown)
			throw exception();
	}
};
bool TestSuiteTestMacro::collapseSetup = false;
bool TestSuiteTestMacro::collapseTearDown = false;

bool collapseSetup = false;
bool collapseTearDown = false;

int testFuncLine = __LINE__ + 1;
TEST_FUNCTION(TestFunctionTest) {
}

SETUP_FUNCTION(SetUp,"Unnamed") {
	if (collapseSetup)
		throw exception();
}

TEARDOWN_FUNCTION(TearDown, "Unnamed") {
	if (collapseTearDown)
		throw exception();
}


int main()
{
	writeTestResult("TestClass tests:",testClassAndMethodMacro);
	writeTestResult("TestFunction tests:", testFunctionMacro);
	writeTestResult("TestClass SetUpAndTearDown:", testClassSetUpAndTearDown);
	
	system("pause");
	return 0;
}

void testClassSetUpAndTearDown() {
	auto testSuite=TestsCollectionExport::getTestContainer().getTestSuiteByName("TestSuiteTestMacro");

	auto results=testSuite->runTestsAndGetReports();
	if (results[0].getResult().isFailure())
		throw SpecialException("Test falling without reason");

	TestSuiteTestMacro::collapseSetup = true;
	results = testSuite->runTestsAndGetReports();
	TestSuiteTestMacro::collapseSetup = false;
	int textPos = results[0].getResult().getCause().find("SetUp");
	if (textPos<0)
		throw SpecialException("Test not have setted SetUp");

	
	TestSuiteTestMacro::collapseTearDown = true;
	results = testSuite->runTestsAndGetReports();
	TestSuiteTestMacro::collapseTearDown = false;
	textPos = results[0].getResult().getCause().find("TearDown");
	if (textPos<0)
		throw SpecialException("Test not have setted TearDown");
	
	cout << "Success";
}

void testClassAndMethodMacro()
{
	string name = typeid(TestSuiteTestMacro).name();
	name = name.substr(strlen("class "));
	testTestCaseMacro(name, "FirstTestMethod", __FILE__, testMethodLine);
}

void testFunctionMacro() {
	testTestCaseMacro("Unnamed", "TestFunctionTest", __FILE__, testFuncLine);
}

