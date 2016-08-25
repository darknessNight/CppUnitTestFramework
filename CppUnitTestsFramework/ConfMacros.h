#pragma once

#define SETUP_METHOD(NAME) \
::darknessNight_CppUnitTestFramework::SetUpRegister NAME##SetUpRegister =\
::darknessNight_CppUnitTestFramework::SetUpRegister([=](){this->NAME();}, this);\
void NAME()


#define TEARDOWN_METHOD(NAME) \
::darknessNight_CppUnitTestFramework::TearDownRegister NAME##SetUpRegister =\
::darknessNight_CppUnitTestFramework::TearDownRegister([=](){this->NAME();}, this);\
void NAME()


#define SETUP_FUNCTION_DECLARE(NAME,SUITE) \
void NAME();\
static ::darknessNight_CppUnitTestFramework::SetUpRegister NAME##SetUpRegister =\
::darknessNight_CppUnitTestFramework::SetUpRegister(&NAME, SUITE);

#define SETUP_FUNCTION(NAME,SUITE) \
SETUP_FUNCTION_DECLARE(NAME,SUITE) \
void NAME()


#define TEARDOWN_FUNCTION_DECLARE(NAME, SUITE) \
void NAME();\
static ::darknessNight_CppUnitTestFramework::TearDownRegister NAME##SetUpRegister =\
::darknessNight_CppUnitTestFramework::TearDownRegister(&NAME, SUITE);

#define TEARDOWN_FUNCTION(NAME, SUITE) \
TEARDOWN_FUNCTION_DECLARE(NAME, SUITE)\
void NAME()