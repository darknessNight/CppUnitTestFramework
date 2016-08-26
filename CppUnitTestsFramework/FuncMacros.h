#pragma once
#include "TestRegisters.h"


#pragma region function added to TestSuite
#define TEST_FUNCTION_IN_SUITE_DECLARE(FUNC_NAME, SUITE) \
void FUNC_NAME();\
static ::darknessNight_CppUnitTestFramework::TestFuncRegister FUNC_NAME##Register(FUNC_NAME,#FUNC_NAME, SUITE, __FILE__, __LINE__);


#define TEST_FUNCTION_IN_SUITE(FUNC_NAME, SUITE) \
TEST_FUNCTION_IN_SUITE_DECLARE(FUNC_NAME, SUITE) \
void FUNC_NAME()

#pragma endregion




#pragma region function added to Unnamed TestSuite
#define TEST_FUNCTION(FUNC_NAME) TEST_FUNCTION_IN_SUITE(FUNC_NAME,"")

#define TEST_FUNCTION_DECLARE(FUNC_NAME) TEST_FUNCTION_IN_SUITE_DECLARE(FUNC_NAME,"")

#pragma endregion




#pragma region parameterized functions 
#define ARG_TEST_FUNCTION_2(FUNCTION_NAME, SUITE, ITER, ...) \
static ::darknessNight_CppUnitTestFramework::TestFuncRegister FUNCTION_NAME##FuncRegister##ITER\
= ::darknessNight_CppUnitTestFramework::TestFuncRegister([&]() {FUNCTION_NAME(__VA_ARGS__); }, #FUNCTION_NAME " (" #__VA_ARGS__ ")", SUITE, __FILE__, __LINE__);

#define ARG_TEST_FUNCTION_1(FUNCTION_NAME, SUITE, ITER, ...) ARG_TEST_FUNCTION_2(FUNCTION_NAME, SUITE, ITER, __VA_ARGS__)
#define ARG_TEST_FUNCTION(FUNCTION_NAME, ...) ARG_TEST_FUNCTION_1(FUNCTION_NAME, "", __COUNTER__, __VA_ARGS__)

#define ARG_TEST_FUNCTION_IN_SUITE(FUNCTION_NAME, SUITE, ...) ARG_TEST_FUNCTION_1(FUNCTION_NAME, SUITE, __COUNTER__, __VA_ARGS__)

#pragma endregion



#pragma region ignored functions
#define IGNORE_TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME, SUITE, IGNORE_CAUSE) \
void FUNC_NAME()

#define IGNORE_TEST_FUNCTION(FUNC_NAME, IGNORE_CAUSE) TEST_FUNCTION_IN_SUITE_CASE(FUNC_NAME,"", IGNORE_CAUSE)
#pragma endregion