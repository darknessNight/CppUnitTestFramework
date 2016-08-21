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
		AssertTestResult(string message) :TestResult(message) {
			errorCause = assertMessage;
		}

		AssertTestResult(const char* message) :TestResult(message) {
			errorCause = assertMessage;
		}
	};

	class ExceptionTestResult :public TestResult {
	private:
		const string exceptionMessage = "C++ exception";
	public:
		ExceptionTestResult(string message) :TestResult(message) {
			errorCause = exceptionMessage;
		}

		ExceptionTestResult(const char* message) :TestResult(message) {
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