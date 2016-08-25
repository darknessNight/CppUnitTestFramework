#pragma once
#include "TestSuiteInstanceCreator.h"
#include "TestSuiteClass.h"
#include "TestRegisters.h"


#define TEST_SUITE(NAME)\
::darknessNight::CppUnitTestFramework::TestClassRegister<::darknessNight::CppUnitTestFramework::TestSuite> NAME##ClearSuiteRegister(#NAME);

#define TEST_SUITE_WITH_CATEGORY(NAME, CATEGORY)\
::darknessNight::CppUnitTestFramework::TestClassWithCategoryRegister<::darknessNight::CppUnitTestFramework::TestSuite> NAME##ClearSuiteRegister(#NAME, ::darknessNight::CppUnitTestFramework::TestCategory(CATEGORY));

#define TEST_CLASS(CLASS_NAME) \
class CLASS_NAME;\
::darknessNight::CppUnitTestFramework::TestClassRegister<CLASS_NAME> CLASS_NAME##Register;\
class CLASS_NAME: public ::darknessNight::CppUnitTestFramework::TestSuiteClass

#define TEST_CLASS_WITH_CATEGORY(CLASS_NAME, CATEGORY) \
class CLASS_NAME;\
::darknessNight::CppUnitTestFramework::TestClassWithCategoryRegister<CLASS_NAME> CLASS_NAME##Register(::darknessNight::CppUnitTestFramework::TestCategory(CATEGORY));\
class CLASS_NAME: public ::darknessNight::CppUnitTestFramework::TestSuiteClass


#define TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME, SUITE) \
void FUNC_NAME();\
::darknessNight::CppUnitTestFramework::TestFuncRegister FUNC_NAME##Register(FUNC_NAME,#FUNC_NAME, SUITE, __FILE__, __LINE__);\
void FUNC_NAME()

#define TEST_FUNCTION(FUNC_NAME) TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME,"")



#if (defined(_MSC_VER) && _MSC_VER>=1800)

#define TEST_REGISTER(METHOD_NAME) \
::darknessNight::CppUnitTestFramework::TestMethodRegister METHOD_NAME##MethodRegister \
= ::darknessNight::CppUnitTestFramework::TestMethodRegister([&]() {this->METHOD_NAME(); }, #METHOD_NAME, typeid(*this).name(), __FILE__, __LINE__);

#elif (defined (__GNUG__))

#define TEST_REGISTER(METHOD_NAME) \
TestMethodRegister METHOD_NAME##MethodRegister \
= TestMethodRegister((ConfigurableTest::TestMethod)&METHOD_NAME, #METHOD_NAME, this, __FILE__, __LINE__);

#else
#error Not supported compiler
#endif


#define TEST_METHOD(METHOD_NAME) \
TEST_REGISTER(METHOD_NAME)\
void METHOD_NAME()



#define SETUP_METHOD(NAME) \
::darknessNight::CppUnitTestFramework::SetUpRegister NAME##SetUpRegister =\
::darknessNight::CppUnitTestFramework::SetUpRegister([=](){this->NAME();}, this);\
void NAME()

#define TEARDOWN_METHOD(NAME) \
::darknessNight::CppUnitTestFramework::TearDownRegister NAME##SetUpRegister =\
::darknessNight::CppUnitTestFramework::TearDownRegister([=](){this->NAME();}, this);\
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