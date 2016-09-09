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
		public:
			TestResult(bool result);
			TestResult(const char* message);
			TestResult(std::string message);
			std::string getFullMessage();
			std::string getErrorMessage();
			std::string getCause();
			TimeDuration getDurationTime();
			void setDurationTime(TimeDuration time);
			bool isSuccess();
			bool isFailure();
		};
	}
}