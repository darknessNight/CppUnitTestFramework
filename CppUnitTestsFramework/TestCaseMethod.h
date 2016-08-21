#pragma once
#include "TestCase.h"

namespace darknessNight::CppUnitTestFramework {
	class TestCaseMethod :public TestCase{
	private:
		ConfigurableTest::TestMethod testMethod=nullptr;
		std::shared_ptr<ConfigurableTest> object=nullptr;
	public:
		TestCaseMethod(ConfigurableTest::TestMethod method) {
			testMethod = method;
		}

		void setTestObj(std::shared_ptr<ConfigurableTest> obj) {
			object = obj;
			test = FunctionTesterPtr(new FunctionTester(std::bind(testMethod,obj)));
		}

		TestResult runTest()override {
			if(object==nullptr || testMethod==nullptr)
				throw std::exception();
			return TestCase::runTest();
		}
	};
}
