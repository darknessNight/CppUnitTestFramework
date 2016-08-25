#pragma once
#include "TestSuiteCreator.h"


namespace darknessNight::CppUnitTestFramework {
	template <typename TestSuiteType> class TestSuiteInstanceCreator :public TestSuiteCreator {
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