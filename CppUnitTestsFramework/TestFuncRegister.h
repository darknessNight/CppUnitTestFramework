#pragma once
#include "TestCaseRegister.h"
#include "TestCaseFunc.h"

namespace darknessNight::CppUnitTestFramework {
	class TestFuncRegister :TestCaseRegister {
	public:
		TestFuncRegister(std::function<void()> func, string testCaseName, string testSuite) {
			auto suite = getTestSuite(testSuite);
			addTestCase(func, testCaseName, suite);
		}
	protected:
		void addTestCase(std::function<void()> func, std::string &name, darknessNight::CppUnitTestFramework::TestSuitePtr &suite)
		{
			TestCasePtr testCase(new TestCaseFunc(func, name));
			suite->addTestCase(testCase);
		}
	};
}