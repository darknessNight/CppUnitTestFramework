#pragma once
#include <functional>
#include "TestResult.h"
#include "ConfigurableTest.h"
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
			catch (std::exception ex) {
				return TestResult(ex.what());
			}
			return TestResult(true);
		}
	};
}
