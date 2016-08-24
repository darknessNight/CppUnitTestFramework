#pragma once
#include "TestRegisterContainerAccess.h"
#include "TestCaseFunc.h"

namespace darknessNight::CppUnitTestFramework {
	class TestFuncRegister :TestRegisterContainerAccess {
	public:
		TestFuncRegister(std::function<void()> func, string funcName, string suiteName, string file, int line) {
			TestCasePtr testCase=addTestCase(func, funcName, file, line);
			getTestContainer().registerTestCase(suiteName, testCase);
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