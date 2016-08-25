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
		TestResult(bool result);
		TestResult(const char* message);
		TestResult(string message);
		string getFullMessage();
		string getErrorMessage();
		string getCause();
		bool isSuccess();
		bool isFailure();
	};
}