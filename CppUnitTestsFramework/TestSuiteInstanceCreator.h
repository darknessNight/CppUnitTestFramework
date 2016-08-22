#pragma once
#include "TestSuite.h"

namespace darknessNight::CppUnitTestFramework {
	template <typename TestSuiteType> class TestSuiteInstanceCreator {
	private:
		std::string suiteName;
		TestSuitePtr testSuite=nullptr;
	public:
		TestSuiteInstanceCreator(std::string name) {
			suiteName = name;
		}

		std::string getSuiteName() {
			return suiteName;
		}

		TestSuitePtr createInstance() {
			createIfNeeded();
			return testSuite;
		}
	private:
		void createIfNeeded() {
			if (testSuite == nullptr)
				testSuite = TestSuitePtr(static_cast<TestSuite*>(new TestSuiteType));
		}
	};
}