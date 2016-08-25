#pragma once
#include "TestSuiteInstanceCreator.h"
#include "TestSuiteClass.h"
#include "TestRegisters.h"

#define TEST_SUITE(NAME)\
static ::darknessNight_CppUnitTestFramework::TestClassRegister<::darknessNight_CppUnitTestFramework::TestSuite> NAME##ClearSuiteRegister(#NAME);

#define TEST_SUITE_WITH_CATEGORY(NAME, CATEGORY)\
static ::darknessNight_CppUnitTestFramework::TestClassWithCategoryRegister<::darknessNight_CppUnitTestFramework::TestSuite> NAME##ClearSuiteRegister(#NAME, ::darknessNight_CppUnitTestFramework::TestCategory(CATEGORY));

#define TEST_CLASS(CLASS_NAME) \
class CLASS_NAME;\
static ::darknessNight_CppUnitTestFramework::TestClassRegister<CLASS_NAME> CLASS_NAME##Register;\
class CLASS_NAME: public ::darknessNight_CppUnitTestFramework::TestSuiteClass

#define TEST_CLASS_WITH_CATEGORY(CLASS_NAME, CATEGORY) \
class CLASS_NAME;\
static ::darknessNight_CppUnitTestFramework::TestClassWithCategoryRegister<CLASS_NAME> CLASS_NAME##Register(::darknessNight_CppUnitTestFramework::TestCategory(CATEGORY));\
class CLASS_NAME: public ::darknessNight_CppUnitTestFramework::TestSuiteClass
