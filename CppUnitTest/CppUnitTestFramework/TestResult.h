#pragma once
#include <string>
#include <chrono>

namespace darknessNight {
	namespace CppUnitTestFramework {
		class TestResult {
		public:
			typedef std::chrono::nanoseconds TimeDuration;
			typedef std::chrono::high_resolution_clock::time_point TimePoint;
		protected:
			bool isTestSuccess;
			std::string errorMessage;
			std::string errorCause;
			TimePoint startTime;
			TimePoint endTime;
			friend class FunctionTester;
		public:
			explicit TestResult(bool result);
			explicit TestResult(const char* message);
			explicit TestResult(std::string message);
			std::string getFullMessage();
			std::string getErrorMessage();
			std::string getCause();
			TimePoint getStartTime();
			TimePoint getEndTime();
			TimeDuration getDurationTime();
			bool isSuccess();
			bool isFailure();
		};
	}
}
