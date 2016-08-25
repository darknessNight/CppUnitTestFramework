#include "TestCaseMethod.h"

using namespace darknessNight::CppUnitTestFramework;

darknessNight::CppUnitTestFramework::TestCaseMethod::TestCaseMethod(ConfigurableTest::TestMethod method, std::string name) {
	testMethod = method;
	setName(name);
}

void darknessNight::CppUnitTestFramework::TestCaseMethod::setTestObj(ConfigurableTest * obj) {
	object = obj;
	functionTester = FunctionTesterPtr(new FunctionTester(std::bind(testMethod, obj)));
}

TestResult darknessNight::CppUnitTestFramework::TestCaseMethod::runTest() {
	throwExceptionIfCannotRunTest();
	return TestCase::runTest();
}

void darknessNight::CppUnitTestFramework::TestCaseMethod::throwExceptionIfCannotRunTest()
{
	if (object == nullptr || testMethod == nullptr)
		throw std::exception("TestCaseMethod not have test object or testMethod in " __FILE__);
}
