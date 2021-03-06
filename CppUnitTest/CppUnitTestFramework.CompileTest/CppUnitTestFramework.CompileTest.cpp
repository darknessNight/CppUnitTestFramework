// CppUnitTestFramework.CompileTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include "CppUnitTestFramework.CompileTest.h"



using namespace darknessNight::CppUnitTestFramework;

int main()
{
	writeTestResult("TestClass tests:",testClassAndMethodMacro);
	writeTestResult("TestFunction tests:", testFunctionMacro);
	writeTestResult("TestClass SetUpAndTearDown:", testClassSetUpAndTearDown);
	writeTestResult("TestClass ArgTestMethodAndFunc:", testArgMethodAndFunc);
	writeTestResult("IgnoreTest:", testIgnoreMethod);
	
	system("pause");
	return 0;
}