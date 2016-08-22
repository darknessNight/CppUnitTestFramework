#pragma once
#include "TestCase.h"

namespace darknessNight::CppUnitTestFramework {
	class TestCaseMethod :public TestCase{
	private:
		ConfigurableTest::TestMethod testMethod=nullptr;
		ConfigurableTest* object=nullptr;
	public:
		TestCaseMethod(ConfigurableTest::TestMethod method, std::string name="") {
			testMethod = method;
			setName(name);
		}

		void setTestObj(ConfigurableTest* obj) {
			object = obj;
			functionTester = FunctionTesterPtr(new FunctionTester(std::bind(testMethod,obj)));
		}

		TestResult runTest()override {
			if(object==nullptr || testMethod==nullptr)
				throw std::exception("TestCaseMethod not have test object or testMethod in " __FILE__);
			return TestCase::runTest();
		}
	};
}
