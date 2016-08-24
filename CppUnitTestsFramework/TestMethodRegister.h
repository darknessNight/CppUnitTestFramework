#pragma once
#include "TestCaseRegister.h"
#include "TestCaseMethod.h"

namespace darknessNight::CppUnitTestFramework {
	class TestMethodRegister :TestCaseRegister {
	public:
		TestMethodRegister(ConfigurableTest::TestMethod method, string methodName, string suiteName, string file, int line) {
			auto testSuite = getTestSuite(suiteName);
			TestCasePtr testCase = addTestCase(method, methodName, file, line);
			testSuite->addTestCase(testCase);
		}
	protected:
		TestCasePtr addTestCase(ConfigurableTest::TestMethod method, string &name, string file, int line)
		{
			TestCasePtr testCase(new TestCaseMethod(method, name));
			testCase->setFileAndLine(file, line);
			return testCase;
		}
	};
}