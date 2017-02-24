#pragma once
#include "TestResult.h"
#include "Exceptions.h"

namespace darknessNight {
	namespace CppUnitTestFramework {

		class AssertTestResult :public TestResult {
		public:
			AssertTestResult(exception ex) :TestResult(ex.what()) {
				errorCause = "Assert failed";
			}
		};

		class ExceptionTestResult :public TestResult {
		public:
			ExceptionTestResult(exception ex) :TestResult(ex.what()) {
				errorCause = "C++ exception";
			}
		};

		class TearDownFailedTestResult :public TestResult {
		public:
			TearDownFailedTestResult(exception ex) :TestResult(ex.what()) {
				errorCause = "TearDown failed";
			}
		};

		class SetUpFailedTestResult :public TestResult {
		public:
			SetUpFailedTestResult(exception ex) :TestResult(ex.what()) {
				errorCause = "SetUp failed";
			}
		};

		class SuccessTestResult :public TestResult {
		public:
			SuccessTestResult() :TestResult(true) {
				errorCause = "Success";
			}
		};

		class IgnoredTestResult :public TestResult {
		public:
			IgnoredTestResult(std::string ignoredCause) :TestResult(true) {
				errorCause = "Ignored";
				errorMessage = ignoredCause;
			}
		};
	}
}