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
			setUp();
			testMethod();
			tearDown();
			return true;
		}
	};
}