// CppUnitTestFramework.CompileTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <CppUnitTestsFramework\Framework.h>
#include <iostream>
#include "CppUnitTestFramework.CompileTest.h"



using namespace darknessNight_CppUnitTestFramework;

int main()
{
	writeTestResult("TestClass tests:",testClassAndMethodMacro);
	writeTestResult("TestFunction tests:", testFunctionMacro);
	writeTestResult("TestClass SetUpAndTearDown:", testClassSetUpAndTearDown);
	
	system("pause");
	return 0;
}

void testClassAndMethodMacro()
{
	std::string name=getClassName<TestSuiteTestMacro>();
	testTestCaseMacro(name, "FirstTestMethod", macrosFile, testMethodLine);
}

void testFunctionMacro() {
	testTestCaseMacro("Unnamed", "TestFunctionTest", macrosFile, testFuncLine);
}

