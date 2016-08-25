#pragma once
#include "TestRegisterContainerAccess.h"
#include "TestCaseMethod.h"
#include "HelperFuncs.h"

namespace darknessNight::CppUnitTestFramework {
	class TestMethodRegister :TestRegisterContainerAccess {
	public:
		TestMethodRegister(std::function<void()> method , string methodName, string suiteName, string file, int line) {
			TestCasePtr testCase = addTestCase(method, methodName, file, line);
			registerTestCase(suiteName, testCase);
		}

	public:
		TestMethodRegister(ConfigurableTest::TestMethod method, string methodName, ConfigurableTest* suite, string file, int line)
		:TestMethodRegister([=]() {(suite->*method)(); } , methodName, typeid(*suite).name() ,file,line){
		}

	public:
		TestMethodRegister(ConfigurableTest::TestMethod method, string methodName,string suiteName, string file, int line){
			TestCasePtr testCase = addTestCaseMethod(method, methodName, file, line);
			registerTestCase(suiteName, testCase);
		}

	protected:
		void registerTestCase(std::string &suiteName, darknessNight::CppUnitTestFramework::TestCasePtr &testCase)
		{
			suiteName = extractClassName(suiteName);
			getTestContainer().registerTestCase(suiteName, testCase);
		}

		TestCasePtr addTestCase(std::function<void()> method, string &name, string file, int line)
		{
			TestCasePtr testCase(new TestCaseFunc(method, name));
			testCase->setFileAndLine(file, line);
			return testCase;
		}

		TestCasePtr addTestCaseMethod(ConfigurableTest::TestMethod method, string &name, string file, int line)
		{
			TestCasePtr testCase(new TestCaseMethod(method, name));
			testCase->setFileAndLine(file, line);
			return testCase;
		}
	};
}