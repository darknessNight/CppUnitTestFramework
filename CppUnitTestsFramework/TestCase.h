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
			TestResult result(true);
			setUp();
			result = runTestMethod();
			tearDown();
			return result;
		}

	private:
		TestResult runTestMethod()
		{
			try {
				testMethod();
			}
			catch (AssertException ex) {
				return AssertTestResult(ex.what());
			}
			catch (std::exception ex) {
				return ExceptionTestResult(ex.what());
			}
			return SuccessTestResult();
		}
	};
}
