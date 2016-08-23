#pragma once
#include "TestSuiteInstanceCreator.h"
#include "TestSuiteClass.h"
#include "TestRegisterer.h"

namespace darknessNight::CppUnitTestFramework {
	//TestKeeper testKeeper;

#define TEST_CLASS(CLASS_NAME) \
class CLASS_NAME;\
TestClassRegister<CLASS_NAME> CLASS_NAME##Register(typeid(CLASS_NAME).name());\
class CLASS_NAME: public TestSuiteClass


	TEST_CLASS(TestSuiteTestMacro) {

	};
}