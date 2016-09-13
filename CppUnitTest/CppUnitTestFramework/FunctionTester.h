#pragma once
#include <functional>
#include "TestResult.h"
#include "ConfigurableTest.h"

namespace darknessNight {
	namespace CppUnitTestFramework {
		class FunctionTester :public ConfigurableTest {
		public:
			typedef std::function<void()> TestMethod;
		private:
			TestMethod testMethod;
		public:
			FunctionTester(TestMethod test);
			virtual TestResult runTest();
		protected:
			TestResult runTestWithoutDuration();
			void throwExceptionIfTestIsNullptr(TestMethod test);
			void FunctionTester::setTestDuration(std::chrono::steady_clock::time_point start, TestResult& testResult);
			TestResult tryRunTest();
			void runSetUpMethod();
			void runTearDownMethod();
			TestResult runTestMethod() const;
		};
	}
}