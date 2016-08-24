#pragma once
#include "TestSuiteInstanceCreator.h"
#include "TestSuiteClass.h"
#include "TestRegisterer.h"


#define TEST_CLASS(CLASS_NAME) \
class CLASS_NAME;\
::darknessNight::CppUnitTestFramework::TestClassRegister<CLASS_NAME> CLASS_NAME##Register;\
class CLASS_NAME: public ::darknessNight::CppUnitTestFramework::TestSuiteClass


#define TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME, SUITE) \
void FUNC_NAME();\
::darknessNight::CppUnitTestFramework::TestFuncRegister FUNC_NAME##Register(FUNC_NAME,#FUNC_NAME, SUITE, __FILE__, __LINE__);\
void FUNC_NAME()

#define TEST_FUNCTION(FUNC_NAME) TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME,"")



#if (defined(_MSC_VER) && _MSC_VER>=1800)
#define TEST_REGISTER(METHOD_NAME) \
void METHOD_NAME##MethodCaller() {METHOD_NAME();}\
TestMethodRegisterHandler_VS<(ConfigurableTest::TestMethod)&METHOD_NAME##MethodCaller> handler;\
TestMethodRegister_VS addFunc = TestMethodRegister_VS(handler, #METHOD_NAME, typeid(*this).name(), __FILE__, __LINE__);
#elif (defined (__GNUG__))
#define TEST_REGISTER(METHOD_NAME) \
TestMethodRegister METHOD_NAME##MethodRegister \
= TestMethodRegister((ConfigurableTest::TestMethod)&METHOD_NAME, #METHOD_NAME, typeid(*this).name(), __FILE__, __LINE__);
#else
#error Not supported compiler
#endif


#define TEST_METHOD(METHOD_NAME) \
TEST_REGISTER(METHOD_NAME)\
void METHOD_NAME()



#define IGNORE_TEST_CLASS(CLASS_NAME, IGNORE_CAUSE)\
class CLASS_NAME{

#define IGNORE_TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME, SUITE, IGNORE_CAUSE) \
void FUNC_NAME(){

#define IGNORE_TEST_FUNCTION(FUNC_NAME, IGNORE_CAUSE) TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME,"", IGNORE_CAUSE)

#define IGNORE_TEST_METHOD(FUNC_NAME, IGNORE_CAUSE) \
void FUNC_NAME()