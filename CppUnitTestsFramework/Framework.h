#pragma once
#include "TestSuiteInstanceCreator.h"
#include "TestSuiteClass.h"
#include "TestRegisters.h"


#if (!defined(_MSC_VER) && __cplusplus<201103L) || (defined(_MSC_VER) && _MSC_VER<=1700)
#error Required C++11 copability compiler
#endif


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





#define TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME, SUITE) \
void FUNC_NAME();\
static ::darknessNight_CppUnitTestFramework::TestFuncRegister FUNC_NAME##Register(FUNC_NAME,#FUNC_NAME, SUITE, __FILE__, __LINE__);\
void FUNC_NAME()

#define TEST_FUNCTION(FUNC_NAME) TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME,"")






#define TEST_METHOD(METHOD_NAME) \
::darknessNight_CppUnitTestFramework::TestMethodRegister METHOD_NAME##MethodRegister \
= ::darknessNight_CppUnitTestFramework::TestMethodRegister([&]() {this->METHOD_NAME(); }, #METHOD_NAME, typeid(*this).name(), __FILE__, __LINE__);\
void METHOD_NAME()





#define TEST_METHOD(METHOD_NAME) \
::darknessNight_CppUnitTestFramework::TestMethodRegister METHOD_NAME##MethodRegister \
= ::darknessNight_CppUnitTestFramework::TestMethodRegister([&]() {this->METHOD_NAME(); }, #METHOD_NAME, typeid(*this).name(), __FILE__, __LINE__);\
void METHOD_NAME()





#define SETUP_METHOD(NAME) \
::darknessNight_CppUnitTestFramework::SetUpRegister NAME##SetUpRegister =\
::darknessNight_CppUnitTestFramework::SetUpRegister([=](){this->NAME();}, this);\
void NAME()

#define TEARDOWN_METHOD(NAME) \
::darknessNight_CppUnitTestFramework::TearDownRegister NAME##SetUpRegister =\
::darknessNight_CppUnitTestFramework::TearDownRegister([=](){this->NAME();}, this);\
void NAME()

#define SETUP_FUNCTION(NAME,SUITE) \
void NAME()

#define TEARDOWN_FUNCTION(NAME, SUITE) \
void NAME()






#define IGNORE_TEST_CLASS(CLASS_NAME, IGNORE_CAUSE)\
class CLASS_NAME{

#define IGNORE_TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME, SUITE, IGNORE_CAUSE) \
void FUNC_NAME(){

#define IGNORE_TEST_FUNCTION(FUNC_NAME, IGNORE_CAUSE) TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME,"", IGNORE_CAUSE)

#define IGNORE_TEST_METHOD(FUNC_NAME, IGNORE_CAUSE) \
void FUNC_NAME()
