#pragma once
#include "TestRegisterContainerAccess.h"

namespace darknessNight::CppUnitTestFramework {
	class SetUpRegister: TestRegisterContainerAccess {
	public:
		SetUpRegister(std::function<void()> func, string suiteName) {
			getTestContainer().registerSetUp(suiteName, func);
		}
	};

	class TearDownRegister : TestRegisterContainerAccess {
	public:
		TearDownRegister(std::function<void()> func, string suiteName) {
			getTestContainer().registerTearDown(suiteName, func);
		}
	};
}