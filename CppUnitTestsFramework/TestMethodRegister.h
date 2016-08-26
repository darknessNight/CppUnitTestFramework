#pragma once
#include "TestRegisterContainerAccess.h"
#include "HelperFuncs.h"

namespace darknessNight_CppUnitTestFramework {
	class TestMethodRegister :TestRegisterContainerAccess {
	public:
		TestMethodRegister(std::function<void()> method , std::string methodName, std::string suiteName, std::string file, int line) {
			TestCasePtr testCase = addTestCase(method, methodName, file, line);
			registerTestCase(suiteName, testCase);
		}

	protected:
		void registerTestCase(std::string &suiteName, darknessNight_CppUnitTestFramework::TestCasePtr &testCase)
		{
			suiteName = extractClassName(suiteName);
			getTestContainer().registerTestCase(suiteName, testCase);
		}

		TestCasePtr addTestCase(std::function<void()> method, std::string &name, std::string file, int line)
		{
			TestCasePtr testCase(new TestCaseFunc(method, name));
			testCase->setFileAndLine(file, line);
			return testCase;
		}
	};
}