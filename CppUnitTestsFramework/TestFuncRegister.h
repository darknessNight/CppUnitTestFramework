#pragma once
#include "TestRegisterContainerAccess.h"
#include "TestCaseFunc.h"

namespace darknessNight_CppUnitTestFramework {
	class TestFuncRegister :TestRegisterContainerAccess {
	public:
		TestFuncRegister(std::function<void()> func, std::string funcName, std::string suiteName, std::string file, int line) {
			TestCasePtr testCase=addTestCase(func, funcName, file, line);
			getTestContainer().registerTestCase(suiteName, testCase);
		}
	protected:
		TestCasePtr addTestCase(std::function<void()> func, std::string &name, std::string file, int line)
		{
			TestCasePtr testCase(new TestCaseFunc(func, name));
			testCase->setFileAndLine(file, line);
			return testCase;
		}
	};
}