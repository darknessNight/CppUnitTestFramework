#pragma once
#include "TestResult.h"

namespace darknessNight::CppUnitTestFramework {

	class AssertTestResult :public TestResult {
	private:
		const string assertMessage = "Assert failed";
	public:
		AssertTestResult(exception ex) :TestResult(ex.what()) {
			errorCause = assertMessage;
		}
	};

	class ExceptionTestResult :public TestResult {
	private:
		const string exceptionMessage = "C++ exception";
	public:
		ExceptionTestResult(exception ex) :TestResult(ex.what()) {
			errorCause = exceptionMessage;
		}
	};

	class TearDownFailedTestResult :public TestResult {
	private:
		const string exceptionMessage = "TearDown failed";
	public:
		TearDownFailedTestResult(exception ex) :TestResult(ex.what()) {
			errorCause = exceptionMessage;
		}
	};

	class SetUpFailedTestResult :public TestResult {
	private:
		const string exceptionMessage = "SetUp failed";
	public:
		SetUpFailedTestResult(exception ex) :TestResult(ex.what()) {
			errorCause = exceptionMessage;
		}
	};

	class SuccessTestResult :public TestResult {
	private:
		const string successMessage = "Success";
	public:
		SuccessTestResult() :TestResult(true) {
			errorCause = successMessage;
		}
	};
}