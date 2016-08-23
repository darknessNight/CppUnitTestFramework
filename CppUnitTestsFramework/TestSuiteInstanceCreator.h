#pragma once
#include "TestSuite.h"

namespace darknessNight::CppUnitTestFramework {
	class TestSuiteCreator {
	public:
		virtual std::string getSuiteName() = 0;
		virtual TestSuitePtr createInstance() = 0;
	};

	template <typename TestSuiteType> class TestSuiteInstanceCreator:public TestSuiteCreator {
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