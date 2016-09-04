#pragma once
#include <string>

namespace darknessNight {
	namespace CppUnitTestFramework {
		class TestResult {
		protected:
			bool isTestSuccess;
			std::string errorMessage;
			std::string errorCause;
		public:
			TestResult(bool result);
			TestResult(const char* message);
			TestResult(std::string message);
			std::string getFullMessage();
			std::string getErrorMessage();
			std::string getCause();
			bool isSuccess();
			bool isFailure();
		};
	}
}