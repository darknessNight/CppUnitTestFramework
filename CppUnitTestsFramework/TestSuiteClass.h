#pragma once
#include "TestCaseMethod.h"
#include "TestSuite.h"

namespace darknessNight::CppUnitTestFramework {
	class TestSuiteClass :public TestSuite {
	protected:
		bool isMethodTestCase(TestCasePtr testCase) {
			TestCaseMethod* castResult = dynamic_cast<TestCaseMethod*>(testCase.get());
			return castResult != nullptr;
		}

		void prepareTestCase(TestCasePtr test) {
			TestSuite::prepareTestCase(test);
			setTestObjectIfNeeded(test);
		}

		void setTestObjectIfNeeded(darknessNight::CppUnitTestFramework::TestCasePtr &test) {
			if (isMethodTestCase(test))
				((TestCaseMethod*)test.get())->setTestObj(this);
		}
	};

}