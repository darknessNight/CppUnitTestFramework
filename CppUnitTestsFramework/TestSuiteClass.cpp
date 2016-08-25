#include "TestSuiteClass.h"

bool darknessNight::CppUnitTestFramework::TestSuiteClass::isMethodTestCase(TestCasePtr testCase) {
	TestCaseMethod* castResult = dynamic_cast<TestCaseMethod*>(testCase.get());
	return castResult != nullptr;
}

void darknessNight::CppUnitTestFramework::TestSuiteClass::prepareTestCase(TestCasePtr test) {
	TestSuite::prepareTestCase(test);
	setTestObjectIfNeeded(test);
}

void darknessNight::CppUnitTestFramework::TestSuiteClass::setTestObjectIfNeeded(darknessNight::CppUnitTestFramework::TestCasePtr & test) {
	if (isMethodTestCase(test))
		((TestCaseMethod*)test.get())->setTestObj(this);
}
