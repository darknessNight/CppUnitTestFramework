#pragma once
#include "TestSuite.h"

namespace darknessNight::CppUnitTestFramework {
	class TestSuiteCreator {
	protected:
		std::string suiteName;
		TestSuitePtr testSuite = nullptr;
		std::vector<TestCasePtr> testCasesArray;
		std::function<void()> setUp;
		std::function<void()> tearDown;
	public:

		std::string getSuiteName() {
			return suiteName;
		}

		TestSuitePtr createInstance() {
			createIfNeeded();
			return testSuite;
		}

		void registerTestCase(TestCasePtr testCase) {
			if (testSuite == nullptr)
				testCasesArray.push_back(testCase);
			else
				testSuite->addTestCase(testCase);
		}

		void registerSetUp(std::function<void()> func) {
			setUp = func;
		}

		void registerTearDown(std::function<void()> func) {
			tearDown = func;
		}

	protected:
		virtual void createIfNeeded() = 0;

		void prepareTestSuite() {
			registerTestToSuite();
			registerConfigurationFuncs();
		}

		void registerConfigurationFuncs()
		{
			testSuite->setSetUpMethod(setUp);
			testSuite->setTearDownMethod(tearDown);
		}

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
				prepareTestSuite();
			}
		}
	};
}