#pragma once
#include <functional>

namespace CppUnitTestsFramework {
	class ConfigurableTest {
	protected:
		virtual void setUp() {
		}
		virtual void tearDown() {
		}
	};

	class TestCase:public ConfigurableTest
	{
	public:
		typedef std::function<void()> TestMethod;
	private:
		TestMethod testMethod;


	public:
		TestCase(TestMethod test) {
			testMethod = test;
		}

		bool runTest() {
			bool result = true;
			setUp();
			result=runTestMethod();
			tearDown();
			return result;
		}

	private:
		bool runTestMethod()
		{
			bool testRunResult = true;
			try {
				testMethod();
			}
			catch (std::exception) {
				testRunResult = false;
			}
			return testRunResult;
		}
	};
}