#pragma once
#include "TestCaseMethod.h"
#include "TestSuite.h"

namespace darknessNight::CppUnitTestFramework {
	class TestSuiteClass :public TestSuite {
	protected:
		bool isMethodTestCase(TestCasePtr testCase);
		void prepareTestCase(TestCasePtr test) override;
		void setTestObjectIfNeeded(darknessNight::CppUnitTestFramework::TestCasePtr &test);
	};

}