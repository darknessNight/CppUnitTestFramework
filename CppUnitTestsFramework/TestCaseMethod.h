#pragma once
#include "TestCase.h"

namespace darknessNight_CppUnitTestFramework {
	class TestCaseMethod :public TestCase{
	private:
		ConfigurableTest::TestMethod testMethod=nullptr;
		ConfigurableTest* object=nullptr;
	public:
		TestCaseMethod(ConfigurableTest::TestMethod method, std::string name = "");
		void setTestObj(ConfigurableTest* obj);
		TestResult runTest()override;
		void throwExceptionIfCannotRunTest();
	};
}
