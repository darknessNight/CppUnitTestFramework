#pragma once
#include "TestCase.h"
#include "PredefinedTestResults.h"

namespace darknessNight {
	namespace CppUnitTestFramework {
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
}