#pragma once
#include "TestRegisterContainerAccess.h"

namespace darknessNight::CppUnitTestFramework {
	class SetUpRegister: TestRegisterContainerAccess {
	public:
		SetUpRegister(std::function<void()> func, string suiteName) {
			getTestContainer().registerSetUp(suiteName, func);
		}

		SetUpRegister(std::function<void()> func, ConfigurableTest* suite):
			SetUpRegister(func,string(typeid(*suite).name()).substr(strlen("class ")))
		{}
	};

	class TearDownRegister : TestRegisterContainerAccess {
	public:
		TearDownRegister(std::function<void()> func, string suiteName) {
			getTestContainer().registerTearDown(suiteName, func);
		}

		TearDownRegister(std::function<void()> func, ConfigurableTest* suite) :
			TearDownRegister(func, string(typeid(*suite).name()).substr(strlen("class ")))
		{}
	};
}