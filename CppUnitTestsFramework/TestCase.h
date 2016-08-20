#pragma once
#include <functional>

namespace CppUnitTestsFramework {
	class TestCase
	{
	public:
		typedef std::function<void()> TestMethod;
		bool setUpRunned=false;
	private:
		TestMethod testMethod;


	public:
		TestCase(TestMethod test) {
			testMethod = test;
		}

		bool runTest() {
			testMethod();
			return true;
		}
	};
}