#pragma once
#include "TestCase.h"

namespace darknessNight_CppUnitTestFramework {
	class TestCaseFuncTester :public TestCase {
	protected:
		TestCaseFuncTester() {}
	public:
		TestCaseFuncTester(FunctionTesterPtr& tester, std::string name) {
			functionTester.swap(tester);
			setName(name);
		}
	};

	class TestCaseFunc :public TestCase {
	public:
		TestCaseFunc(std::function<void()> func, std::string name) {
			setName(name);
			functionTester = FunctionTesterPtr(new FunctionTester(func));
		}
	};
}