#pragma once
#include <string>
#include <chrono>

namespace darknessNight {
	namespace CppUnitTestFramework {
		class TestResult {
		public:
			typedef std::chrono::microseconds TimeDuration;
		protected:
			bool isTestSuccess;
			std::string errorMessage;
			std::string errorCause;
			TimeDuration time= TimeDuration::zero();
			friend class FunctionTester;
		public:
			explicit TestResult(bool result);
			explicit TestResult(const char* message);
			explicit TestResult(std::string message);
			std::string getFullMessage();
			std::string getErrorMessage();
			std::string getCause();
			TimeDuration getDurationTime();
			bool isSuccess();
			bool isFailure();
		};
	}
}