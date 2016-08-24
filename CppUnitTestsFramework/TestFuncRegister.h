#pragma once
#include "TestCaseRegister.h"
#include "TestCaseFunc.h"

namespace darknessNight::CppUnitTestFramework {
	class TestFuncRegister :TestCaseRegister {
	public:
		TestFuncRegister(std::function<void()> func, string testCaseName, string testSuite, string file, int line) {
			auto suite = getTestSuite(testSuite);
			TestCasePtr testCase=addTestCase(func, testCaseName, file, line);
			suite->addTestCase(testCase);
		}
	protected:
		TestCasePtr addTestCase(std::function<void()> func, string &name, string file, int line)
		{
			TestCasePtr testCase(new TestCaseFunc(func, name));
			testCase->setFileAndLine(file, line);
			return testCase;
		}
	};
}