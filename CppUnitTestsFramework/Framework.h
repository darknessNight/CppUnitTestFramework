#pragma once
#include "TestSuiteInstanceCreator.h"
#include "TestSuiteClass.h"
#include "TestRegisterer.h"

namespace darknessNight::CppUnitTestFramework {
	//TestKeeper testKeeper;

#define TEST_CLASS(CLASS_NAME) \
class CLASS_NAME;\
::darknessNight::CppUnitTestFramework::TestClassRegister<CLASS_NAME> CLASS_NAME##Register(typeid(CLASS_NAME).name());\
class CLASS_NAME: public ::darknessNight::CppUnitTestFramework::TestSuiteClass
}

#define TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME, SUITE) \
void FUNC_NAME();\
::darknessNight::CppUnitTestFramework::TestFuncRegister FUNC_NAME##Register(FUNC_NAME,#FUNC_NAME, SUITE);\
void FUNC_NAME()

#define TEST_FUNCTION(FUNC_NAME) TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME,"")


#define TEST_METHOD(METHOD_NAME) \
void METHOD_NAME()