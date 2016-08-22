#pragma once
#include <string>
using namespace std;
namespace darknessNight::CppUnitTestFramework {
	class TestResult {
	protected:
		bool isTestSuccess;
		string errorMessage;
		string errorCause;
	public:
		TestResult(bool result) {
			isTestSuccess = result;
			errorMessage = "";
		}

		TestResult(const char* message) :TestResult(string(message)) {
		}

		TestResult(string message) {
			isTestSuccess = false;
			errorMessage = message;
		}

		string getFullMessage() {
			return errorCause+": "+errorMessage;
		}

		string getErrorMessage() {
			return errorMessage;
		}

		string getCause() {
			return errorCause;
		}

		bool isSuccess() {
			return isTestSuccess == true;
		}

		bool isFailure() {
			return isTestSuccess == false;
		}
	};

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