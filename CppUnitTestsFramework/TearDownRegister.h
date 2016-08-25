#pragma once
#include "TestRegisterContainerAccess.h"
#include "HelperFuncs.h"

namespace darknessNight::CppUnitTestFramework {

	class TearDownRegister : TestRegisterContainerAccess {
	public:
		TearDownRegister(std::function<void()> func, string suiteName) {
			getTestContainer().registerTearDown(suiteName, func);
		}

		TearDownRegister(std::function<void()> func, ConfigurableTest* suite) :
			TearDownRegister(func, getClassName(suite))
		{}
	};
}