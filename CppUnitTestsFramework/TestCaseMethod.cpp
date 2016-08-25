#include "TestCaseMethod.h"

using namespace darknessNight_CppUnitTestFramework;

darknessNight_CppUnitTestFramework::TestCaseMethod::TestCaseMethod(ConfigurableTest::TestMethod method, std::string name) {
	testMethod = method;
	setName(name);
}

void darknessNight_CppUnitTestFramework::TestCaseMethod::setTestObj(ConfigurableTest * obj) {
	object = obj;
	functionTester = FunctionTesterPtr(new FunctionTester(std::bind(testMethod, obj)));
}

TestResult darknessNight_CppUnitTestFramework::TestCaseMethod::runTest() {
	throwExceptionIfCannotRunTest();
	return TestCase::runTest();
}

void darknessNight_CppUnitTestFramework::TestCaseMethod::throwExceptionIfCannotRunTest()
{
	if (object == nullptr || testMethod == nullptr)
		throw exception("TestCaseMethod not have test object or testMethod in " __FILE__);
}
