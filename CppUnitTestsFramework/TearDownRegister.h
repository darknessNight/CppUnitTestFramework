#pragma once
#include "TestRegisterContainerAccess.h"
#include "HelperFuncs.h"

namespace darknessNight {
	namespace CppUnitTestFramework {

		class TearDownRegister : TestRegisterContainerAccess {
		public:
			TearDownRegister(std::function<void()> func, std::string suiteName) {
				getTestContainer().registerTearDown(suiteName, func);
			}

			TearDownRegister(std::function<void()> func, ConfigurableTest* suite) :
				TearDownRegister(func, getClassName(suite)) {
			}
		};
	}
}