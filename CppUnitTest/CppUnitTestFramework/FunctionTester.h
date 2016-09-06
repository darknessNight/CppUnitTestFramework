#pragma once
#include <functional>
#include "Exceptions.h"
#include "TestResult.h"
#include "ConfigurableTest.h"
#include "AssertExceptions.h"

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
			TestResult tryRunTestAndSetTime();
			void throwExceptionIfTestIsNullptr(TestMethod test);
			TestResult tryRunTest();
			void runSetUpMethod();
			void runTearDownMethod();
			TestResult runTestMethod();
		};
	}
}