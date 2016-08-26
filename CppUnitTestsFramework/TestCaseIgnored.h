#pragma once
#include "TestCase.h"
#include "PredefinedTestResults.h"

namespace darknessNight_CppUnitTestFramework {
	class TestCaseIgnored :public TestCase {
	private:
		std::string ignoredCause;
	public:
		TestCaseIgnored(std::string name, std::string cause) {
			setName(name);
			ignoredCause = cause;
		}

		TestResult runTest()override {
			IgnoredTestResult testResult(ignoredCause);
			return testResult;
		}
	};
}