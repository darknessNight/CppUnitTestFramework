#pragma once
#include "TestSuiteInstanceCreator.h"
#include "TestRegisters.h"

#pragma region Test suites without classess
#define TEST_SUITE(NAME)\
static ::darknessNight::CppUnitTestFramework::TestClassRegister<::darknessNight::CppUnitTestFramework::TestSuite> NAME##ClearSuiteRegister(#NAME);

#define TEST_SUITE_WITH_CATEGORY(NAME, CATEGORY)\
static ::darknessNight::CppUnitTestFramework::TestClassWithCategoryRegister<::darknessNight::CppUnitTestFramework::TestSuite> NAME##ClearSuiteRegister(#NAME, ::darknessNight::CppUnitTestFramework::TestCategory(CATEGORY));

#pragma endregion



#pragma region Test suites with classess definions
#define TEST_CLASS(CLASS_NAME) \
class CLASS_NAME;\
static ::darknessNight::CppUnitTestFramework::TestClassRegister<CLASS_NAME> CLASS_NAME##Register;\
class CLASS_NAME: public ::darknessNight::CppUnitTestFramework::TestSuite

#define TEST_CLASS_WITH_CATEGORY(CLASS_NAME, CATEGORY) \
class CLASS_NAME;\
static ::darknessNight::CppUnitTestFramework::TestClassWithCategoryRegister<CLASS_NAME> CLASS_NAME##Register(::darknessNight::CppUnitTestFramework::TestCategory(CATEGORY));\
class CLASS_NAME: public ::darknessNight::CppUnitTestFramework::TestSuite

#pragma endregion