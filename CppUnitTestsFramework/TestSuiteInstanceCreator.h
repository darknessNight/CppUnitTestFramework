#pragma once
#include "TestSuiteCreator.h"

namespace darknessNight::CppUnitTestFramework {
	template <typename TestSuiteType> class TestSuiteInstanceCreator :public TestSuiteCreator {
	public:
		TestSuiteInstanceCreator(std::string name) {
			suiteName = name;
		}

		TestSuiteInstanceCreator(std::string name, TestCategory cat) {
			suiteName = name;
			category = cat;
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