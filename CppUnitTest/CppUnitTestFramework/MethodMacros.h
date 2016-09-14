#pragma once

#pragma region Test method
#define TEST_METHOD(METHOD_NAME) \
::darknessNight::CppUnitTestFramework::TestFuncRegister METHOD_NAME##MethodRegister \
= ::darknessNight::CppUnitTestFramework::TestFuncRegister([&]() {this->METHOD_NAME(); }, #METHOD_NAME, this, __FILE__, __LINE__);\
void METHOD_NAME()

#pragma endregion



#pragma region Parameterized test methods
#define ARG_TEST_METHOD_2(METHOD_NAME, ITER, ...) \
::darknessNight::CppUnitTestFramework::TestFuncRegister METHOD_NAME##MethodRegister##ITER\
= ::darknessNight::CppUnitTestFramework::TestFuncRegister([&]() {this->METHOD_NAME(__VA_ARGS__); }, #METHOD_NAME "(" #__VA_ARGS__ ")", this, __FILE__, __LINE__);

#define ARG_TEST_METHOD_1(METHOD_NAME, ITER, ...) ARG_TEST_METHOD_2(METHOD_NAME, ITER, __VA_ARGS__)
#define ARG_TEST_METHOD(METHOD_NAME, ...) ARG_TEST_METHOD_1(METHOD_NAME, __COUNTER__, __VA_ARGS__)

#pragma endregion



#pragma region Ignored test methods
#define IGNORE_TEST_METHOD(FUNC_NAME, IGNORE_CAUSE) \
::darknessNight::CppUnitTestFramework::TestIgnoredRegister FUNC_NAME##RegisterIgnoredTest = \
::darknessNight::CppUnitTestFramework::TestIgnoredRegister(#FUNC_NAME, #IGNORE_CAUSE, this, __FILE__, __LINE__);\
void FUNC_NAME()

#pragma endregion