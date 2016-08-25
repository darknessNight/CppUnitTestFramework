#pragma once
#include "TestCaseMethod.h"
#include "TestSuite.h"

namespace darknessNight_CppUnitTestFramework {
	class TestSuiteClass :public TestSuite {
	protected:
		bool isMethodTestCase(TestCasePtr testCase);
		void prepareTestCase(TestCasePtr test) override;
		void setTestObjectIfNeeded(darknessNight_CppUnitTestFramework::TestCasePtr &test);
	};

}