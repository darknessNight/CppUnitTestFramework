#pragma once
#include "TestSuite.h"

namespace darknessNight {
	namespace CppUnitTestFramework {
		class TestSuiteCreator {
		protected:
			std::string suiteName;
			TestCategory category;
			TestSuitePtr testSuite = nullptr;
			std::vector<TestCasePtr> testCasesArray;
			std::function<void()> setUp;
			std::function<void()> tearDown;
		public:
			TestSuiteCreator(std::string name);
			std::string getSuiteName();
			TestSuitePtr createInstance();
			void registerTestCase(TestCasePtr testCase);
			void registerSetUp(std::function<void()> func);
			void registerTearDown(std::function<void()> func);
		protected:
			TestSuiteCreator();
			virtual void createIfNeeded();
			void prepareTestSuite();
			void saveCategory();
			void registerConfigurationFuncs();
			void registerTestToSuite();
		};
	}
}
