#pragma once
#include "TestResult.h"

namespace darknessNight_CppUnitTestFramework {

	class AssertTestResult :public TestResult {
	private:
		const std::string assertMessage = "Assert failed";
	public:
		AssertTestResult(exception ex) :TestResult(ex.what()) {
			errorCause = assertMessage;
		}
	};

	class ExceptionTestResult :public TestResult {
	private:
		const std::string exceptionMessage = "C++ exception";
	public:
		ExceptionTestResult(exception ex) :TestResult(ex.what()) {
			errorCause = exceptionMessage;
		}
	};

	class TearDownFailedTestResult :public TestResult {
	private:
		const std::string exceptionMessage = "TearDown failed";
	public:
		TearDownFailedTestResult(exception ex) :TestResult(ex.what()) {
			errorCause = exceptionMessage;
		}
	};

	class SetUpFailedTestResult :public TestResult {
	private:
		const std::string exceptionMessage = "SetUp failed";
	public:
		SetUpFailedTestResult(exception ex) :TestResult(ex.what()) {
			errorCause = exceptionMessage;
		}
	};

	class SuccessTestResult :public TestResult {
	private:
		const std::string successMessage = "Success";
	public:
		SuccessTestResult() :TestResult(true) {
			errorCause = successMessage;
		}
	};
}