#pragma once
#include <string>
using namespace std;
namespace darknessNight::CppUnitTestFramework {
	class TestResult {
	private:
		bool isTestSuccess;
		string errorMessage;
	public:
		TestResult(bool result) {
			isTestSuccess = result;
			errorMessage = "";
		}

		TestResult(const char* message) :TestResult(string(message)) {
		}

		TestResult(string message) {
			isTestSuccess = false;
			errorMessage = "MethodFailed";
		}

		string getMessage() {
			return errorMessage;
		}

		bool isSuccess() {
			return isTestSuccess == true;
		}

		bool isFailure() {
			return isTestSuccess == false;
		}
	};
}