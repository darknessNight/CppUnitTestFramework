#pragma once
#include "TestSuite.h"

namespace darknessNight::CppUnitTestFramework {
	class TestSuiteCreator {
	protected:
		std::string suiteName;
		TestSuitePtr testSuite = nullptr;
		std::vector<TestCasePtr> testCasesArray;
	public:

		std::string getSuiteName() {
			return suiteName;
		}

		TestSuitePtr createInstance() {
			createIfNeeded();
			return testSuite;
		}

		void registerTestCase(TestCasePtr testCase) {
			testCasesArray.push_back(testCase);
		}

	protected:
		virtual void createIfNeeded() = 0;

		void registerTestToSuite() {
			for each(auto testCase in testCasesArray)
				testSuite->addTestCase(testCase);
			testCasesArray.clear();
		}
	};

	template <typename TestSuiteType> class TestSuiteInstanceCreator:public TestSuiteCreator {
	public:
		TestSuiteInstanceCreator(std::string name) {
			suiteName = name;
		}

	protected:
		void createIfNeeded() override {
			if (testSuite == nullptr) {
				testSuite = TestSuitePtr(static_cast<TestSuite*>(new TestSuiteType));
				registerTestToSuite();
			}
		}
	};
}