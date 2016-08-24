#pragma once
#include "../TestMethodRegister.h"

namespace darknessNight::CppUnitTestFramework {
	class BasicTestMethodRegisterHandler_VS {
	public:
		virtual ConfigurableTest::TestMethod returnMethod() = 0;
	};

	template <ConfigurableTest::TestMethod method> class TestMethodRegisterHandler_VS : public BasicTestMethodRegisterHandler_VS {
	public:
		ConfigurableTest::TestMethod returnMethod() {
			return method;
		}
	};

	class TestMethodRegister_VS :TestMethodRegister {
	public:
		TestMethodRegister_VS(BasicTestMethodRegisterHandler_VS& method, string methodName, string suiteName, string file, int line) :
			TestMethodRegister(method.returnMethod(), methodName, suiteName, file, line) {}
	};

}