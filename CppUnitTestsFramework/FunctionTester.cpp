#include "FunctionTester.h"
#include "PredefinedTestResults.h"
#include "Exceptions.h"

using namespace darknessNight::CppUnitTestFramework;

darknessNight::CppUnitTestFramework::FunctionTester::FunctionTester(TestMethod test) {
	throwExceptionIfTestIsNullptr(test);
	testMethod = test;
}

void darknessNight::CppUnitTestFramework::FunctionTester::throwExceptionIfTestIsNullptr(TestMethod test) {
		if (test == nullptr)
			throw NullPointerException(std::string("Argument cannot be nullptr in ") + __FILE__ " " + std::to_string(__LINE__));
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
	catch (std::exception ex) {
		exception exception = ex;
		throw SetUpException(exception);
	}
	catch (exception *ex) {
		throw SetUpException(*ex);
	}
	catch (...) {
		exception exception("Unknow exception type");
		throw SetUpException(exception);
	}
}

TestResult darknessNight::CppUnitTestFramework::FunctionTester::runTestMethod(){
	try {
		testMethod();
	}
	catch (AssertFailException ex) {
		return AssertTestResult(ex);
	}
	catch (AssertPassException ex) {
		return SuccessTestResult();
	}
	catch (exception ex) {
		return ExceptionTestResult(ex);
	}
	catch (std::exception ex) {
		return ExceptionTestResult(ex);
	}
	catch (...) {
		exception exception("Unknow exception type");
		return ExceptionTestResult(exception);
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
	catch (std::exception ex) {
		exception exception = ex;
		throw TearDownException(exception);
	}
	catch (exception *ex) {
		throw TearDownException(*ex);
	}
	catch (...) {
		exception exception("Unknow exception type");
		throw SetUpException(exception);
	}
}