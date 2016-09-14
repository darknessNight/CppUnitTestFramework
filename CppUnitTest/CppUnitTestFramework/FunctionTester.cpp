#include "FunctionTester.h"
#include "PredefinedTestResults.h"
#include "Exceptions.h"
#include "Assert.h"

using namespace darknessNight::CppUnitTestFramework;

FunctionTester::FunctionTester(TestMethod test) {
	throwExceptionIfTestIsNullptr(test);
	testMethod = test;
}

void FunctionTester::throwExceptionIfTestIsNullptr(TestMethod test) {
		if (test == nullptr)
			throw NullPointerException(std::string("Argument cannot be nullptr in ") + __FILE__ " " + std::to_string(__LINE__));
}

void FunctionTester::setTestDuration(std::chrono::steady_clock::time_point start, TestResult& testResult) {
	auto end = std::chrono::high_resolution_clock::now();
	testResult.startTime = start;
	testResult.endTime = end;
}

TestResult FunctionTester::runTest() {
	auto start = std::chrono::high_resolution_clock::now();
	auto testResult = runTestWithoutDuration();
	setTestDuration(start, testResult);
	return testResult;
}

TestResult FunctionTester::runTestWithoutDuration() {
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

TestResult FunctionTester::tryRunTest(){
	runSetUpMethod();
	TestResult result = runTestMethod();
	runTearDownMethod();
	return result;
}

void FunctionTester::runSetUpMethod(){
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

TestResult FunctionTester::runTestMethod() const {
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

void FunctionTester::runTearDownMethod(){
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