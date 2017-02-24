#pragma once
#include "TestRegisterContainerAccess.h"
#include "HelperFuncs.h"

namespace darknessNight {
	namespace CppUnitTestFramework {

		class SetUpRegister : TestRegisterContainerAccess {
		public:
			SetUpRegister(std::function<void()> func, std::string suiteName) {
				getTestContainer().registerSetUp(suiteName, func);
			}

			SetUpRegister(std::function<void()> func, ConfigurableTest* suite) :
				SetUpRegister(func, getClassName(suite)) {
			}
		};
	}
}