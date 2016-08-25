#include "FunctionTester.h"
#include "PredefinedTestResults.h"
using namespace darknessNight::CppUnitTestFramework;

darknessNight::CppUnitTestFramework::FunctionTester::FunctionTester(TestMethod test) {
	throwExceptionIfTestIsNullptr(test);
	testMethod = test;
}

void darknessNight::CppUnitTestFramework::FunctionTester::throwExceptionIfTestIsNullptr(TestMethod test) {
		if (test == nullptr)
			throw NullPointerException(string("Argument cannot be nullptr in ") + __FILE__ " " + std::to_string(__LINE__));
}

TestResult darknessNight::CppUnitTestFramework::FunctionTester::runTest() {
	try {
		return tryRunTest();
	}
	catch (SetUpException ex) {
		return SetUpFailedTestResult(ex);
	}
	catch (TearDownException ex) {
		return TearDownFailedTestResult(ex);
	}
}

TestResult darknessNight::CppUnitTestFramework::FunctionTester::tryRunTest(){
	runSetUpMethod();
	TestResult result = runTestMethod();
	runTearDownMethod();
	return result;
}

void darknessNight::CppUnitTestFramework::FunctionTester::runSetUpMethod(){
	try {
		setUp();
	}
	catch (exception ex) {
		throw SetUpException(ex);
	}
	catch (exception *ex) {
		throw SetUpException(*ex);
	}
}

TestResult darknessNight::CppUnitTestFramework::FunctionTester::runTestMethod(){
	try {
		testMethod();
	}
	catch (AssertException ex) {
		return AssertTestResult(ex);
	}
	catch (std::exception ex) {
		return ExceptionTestResult(ex);
	}
	return SuccessTestResult();
}

void darknessNight::CppUnitTestFramework::FunctionTester::runTearDownMethod(){
	try {
		tearDown();
	}
	catch (exception ex) {
		throw TearDownException(ex);
	}
	catch (exception *ex) {
		throw TearDownException(*ex);
	}
}