#pragma once
#include "TestCaseRegister.h"
#include "TestCaseFunc.h"

namespace darknessNight::CppUnitTestFramework {
	class TestFuncRegister :TestCaseRegister {
	public:
		TestFuncRegister(std::function<void()> func, string funcName, string suiteName, string file, int line) {
			auto testSuite = getTestSuite(suiteName);
			TestCasePtr testCase=addTestCase(func, funcName, file, line);
			testSuite->addTestCase(testCase);
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