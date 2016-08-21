#pragma once
#include <functional>
#include "TestResult.h"
#include "ConfigurableTest.h"
#include "AssertExceptions.h"
using namespace std;
namespace darknessNight::CppUnitTestFramework {
	class TestCase :public ConfigurableTest
	{
	public:
		typedef std::function<void()> TestMethod;
	private:
		TestMethod testMethod;

	public:
		TestCase(TestMethod test) {
			testMethod = test;
		}

		TestResult runTest() {
			return tryRunTest();
		}

		TestResult tryRunTest()
		{
			runSetUpMethod();
			TestResult result = runTestMethod();
			runTearDownMethod();
			return result;
		}


	private:
		void runSetUpMethod()
		{
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

		void runTearDownMethod()
		{
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

		TestResult runTestMethod()
		{
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
	};
}
