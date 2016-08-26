#pragma once
#include "TestRegisterContainerAccess.h"
#include "HelperFuncs.h"
#include "TestCaseIgnored.h"

namespace darknessNight_CppUnitTestFramework {
	class TestIgnoredRegister :TestRegisterContainerAccess {
	public:
		TestIgnoredRegister(std::string methodName, std::string ignoredCause, std::string suiteName, std::string file, int line) {
			TestCasePtr testCase = addTestCase(methodName, ignoredCause, file, line);
			registerTestCase(suiteName, testCase);
		}
		
		TestIgnoredRegister(std::string methodName, std::string ignoredCause, TestSuite* suite, std::string file, int line) :
			TestIgnoredRegister(methodName, ignoredCause, getClassName(suite), file,line)
		{
			
		}

	protected:
		void registerTestCase(std::string &suiteName, darknessNight_CppUnitTestFramework::TestCasePtr &testCase)
		{
			getTestContainer().registerTestCase(suiteName, testCase);
		}

		TestCasePtr addTestCase(std::string &name, std::string ignoredCause, std::string file, int line)
		{
			TestCasePtr testCase(new TestCaseIgnored(name, ignoredCause));
			testCase->setFileAndLine(file, line);
			return testCase;
		}
	};
}