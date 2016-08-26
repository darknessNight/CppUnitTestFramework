#pragma once
#pragma region Test method
#define TEST_METHOD(METHOD_NAME) \
::darknessNight_CppUnitTestFramework::TestMethodRegister METHOD_NAME##MethodRegister \
= ::darknessNight_CppUnitTestFramework::TestMethodRegister([&]() {this->METHOD_NAME(); }, #METHOD_NAME, typeid(*this).name(), __FILE__, __LINE__);\
void METHOD_NAME()

#pragma endregion



#pragma region Parameterized test methods
#define ARG_TEST_METHOD_2(METHOD_NAME, ITER, ...) \
::darknessNight_CppUnitTestFramework::TestMethodRegister METHOD_NAME##MethodRegister##ITER\
= ::darknessNight_CppUnitTestFramework::TestMethodRegister([&]() {this->METHOD_NAME(__VA_ARGS__); }, #METHOD_NAME " (" #__VA_ARGS__ ")", typeid(*this).name(), __FILE__, __LINE__);

#define ARG_TEST_METHOD_1(METHOD_NAME, ITER, ...) ARG_TEST_METHOD_2(METHOD_NAME, ITER, __VA_ARGS__)
#define ARG_TEST_METHOD(METHOD_NAME, ...) ARG_TEST_METHOD_1(METHOD_NAME, __COUNTER__, __VA_ARGS__)

#pragma endregion



#pragma region Ignored test methods
#define IGNORE_TEST_METHOD(FUNC_NAME, IGNORE_CAUSE) \
void FUNC_NAME()

#pragma endregion