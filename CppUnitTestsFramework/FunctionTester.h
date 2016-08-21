#pragma once
#include <functional>
#include "TestResult.h"
#include "ConfigurableTest.h"
#include "AssertExceptions.h"
using namespace std;
namespace darknessNight::CppUnitTestFramework {
	class FunctionTester :public ConfigurableTest
	{
	public:
		typedef std::function<void()> TestMethod;
	private:
		TestMethod testMethod;

	public:
		FunctionTester(TestMethod test) {
			if (test == nullptr)
				throw NullPointerException(string("Argument cannot be nullptr in ") + __FILE__ " " + std::to_string(__LINE__));
			testMethod = test;
		}

		virtual TestResult runTest() {
			return tryRunTest();
		}

	protected:
		TestResult tryRunTest()
		{
			runSetUpMethod();
			TestResult result = runTestMethod();
			runTearDownMethod();
			return result;
		}

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
