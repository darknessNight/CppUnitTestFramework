#pragma once
#include "TestSuiteInstanceCreator.h"
#include "TestSuiteClass.h"
#include "TestRegisterer.h"


#define TEST_CLASS(CLASS_NAME) \
class CLASS_NAME;\
::darknessNight::CppUnitTestFramework::TestClassRegister<CLASS_NAME> CLASS_NAME##Register(typeid(CLASS_NAME).name());\
class CLASS_NAME: public ::darknessNight::CppUnitTestFramework::TestSuiteClass


#define TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME, SUITE) \
void FUNC_NAME();\
::darknessNight::CppUnitTestFramework::TestFuncRegister FUNC_NAME##Register(FUNC_NAME,#FUNC_NAME, SUITE, __FILE__, __LINE__);\
void FUNC_NAME()

#define TEST_FUNCTION(FUNC_NAME) TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME,"")


#define TEST_METHOD(METHOD_NAME) \
void METHOD_NAME()



#define IGNORE_TEST_CLASS(CLASS_NAME, IGNORE_CAUSE)\
class CLASS_NAME{

#define IGNORE_TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME, SUITE, IGNORE_CAUSE) \
void FUNC_NAME(){

#define IGNORE_TEST_FUNCTION(FUNC_NAME, IGNORE_CAUSE) TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME,"", IGNORE_CAUSE)

#define IGNORE_TEST_METHOD(FUNC_NAME, IGNORE_CAUSE) \
void FUNC_NAME()