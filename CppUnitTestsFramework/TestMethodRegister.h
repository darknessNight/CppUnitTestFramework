#pragma once
#include "TestRegisterContainerAccess.h"
#include "TestCaseMethod.h"

namespace darknessNight::CppUnitTestFramework {
	class TestMethodRegister :TestRegisterContainerAccess {
	public:
		TestMethodRegister(ConfigurableTest::TestMethod method, string methodName, string suiteName, string file, int line) {
			suiteName = suiteName.substr(strlen("class "));
			TestCasePtr testCase = addTestCase(method, methodName, file, line);
			getTestContainer().registerTestCase(suiteName, testCase);
		}
	protected:
		TestCasePtr addTestCase(ConfigurableTest::TestMethod method, string &name, string file, int line)
		{
			TestCasePtr testCase(new TestCaseMethod(method, name));
			testCase->setFileAndLine(file, line);
			return testCase;
		}
	};

	class BasicTestMethodRegisterHandler_VS {
	public:
		virtual ConfigurableTest::TestMethod returnMethod() = 0;
	};

	template <ConfigurableTest::TestMethod method> class TestMethodRegisterHandler_VS: public BasicTestMethodRegisterHandler_VS {
	public:
		ConfigurableTest::TestMethod returnMethod() {
			return method;
		}
	};
	
	class TestMethodRegister_VS :TestMethodRegister {
	public:
		TestMethodRegister_VS(BasicTestMethodRegisterHandler_VS& method,string methodName, string suiteName, string file,int line):
			TestMethodRegister(method.returnMethod(),methodName,suiteName,file,line){}
	};
}