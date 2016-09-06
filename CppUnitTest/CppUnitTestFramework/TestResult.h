#pragma once
#include <string>
#include <chrono>

namespace darknessNight {
	namespace CppUnitTestFramework {
		class TestResult {
		protected:
			bool isTestSuccess;
			std::string errorMessage;
			std::string errorCause;
			std::chrono::nanoseconds time=std::chrono::nanoseconds::zero();
		public:
			TestResult(bool result);
			TestResult(const char* message);
			TestResult(std::string message);
			std::string getFullMessage();
			std::string getErrorMessage();
			std::string getCause();
			std::chrono::nanoseconds getTime();
			void setTime(std::chrono::nanoseconds time);
			bool isSuccess();
			bool isFailure();
		};
	}
}