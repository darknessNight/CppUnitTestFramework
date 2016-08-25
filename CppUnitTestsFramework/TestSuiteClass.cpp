#include "TestSuiteClass.h"

bool darknessNight_CppUnitTestFramework::TestSuiteClass::isMethodTestCase(TestCasePtr testCase) {
	TestCaseMethod* castResult = dynamic_cast<TestCaseMethod*>(testCase.get());
	return castResult != nullptr;
}

void darknessNight_CppUnitTestFramework::TestSuiteClass::prepareTestCase(TestCasePtr test) {
	TestSuite::prepareTestCase(test);
	setTestObjectIfNeeded(test);
}

void darknessNight_CppUnitTestFramework::TestSuiteClass::setTestObjectIfNeeded(darknessNight_CppUnitTestFramework::TestCasePtr & test) {
	if (isMethodTestCase(test))
		((TestCaseMethod*)test.get())->setTestObj(this);
}
