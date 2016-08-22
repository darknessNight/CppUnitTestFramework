#pragma once
#include "TestSuiteInstanceCreator.h"
#include "TestSuiteClass.h"

namespace darknessNight::CppUnitTestFramework {
	//TestKeeper testKeeper;

#define TEST_CLASS(CLASS_NAME) \
class CLASS_NAME;\
TestSuiteInstanceCreator<CLASS_NAME> CLASS_NAME##Creator (#CLASS_NAME);\
class CLASS_NAME: public TestSuiteClass


	TEST_CLASS(TestSuiteTestMacro) {

	};
}