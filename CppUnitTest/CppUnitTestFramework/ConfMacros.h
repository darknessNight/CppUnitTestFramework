#pragma once

#define SETUP_METHOD(NAME) \
::darknessNight::CppUnitTestFramework::SetUpRegister NAME##SetUpRegister =\
::darknessNight::CppUnitTestFramework::SetUpRegister([=](){this->NAME();}, this);\
void NAME()


#define TEARDOWN_METHOD(NAME) \
::darknessNight::CppUnitTestFramework::TearDownRegister NAME##SetUpRegister =\
::darknessNight::CppUnitTestFramework::TearDownRegister([=](){this->NAME();}, this);\
void NAME()



#define SETUP_FUNCTION_DECLARE(NAME,SUITE) \
void NAME();\
static ::darknessNight::CppUnitTestFramework::SetUpRegister NAME##SetUpRegister =\
::darknessNight::CppUnitTestFramework::SetUpRegister(&NAME, SUITE);

#define SETUP_FUNCTION(NAME,SUITE) \
SETUP_FUNCTION_DECLARE(NAME,SUITE) \
void NAME()



#define TEARDOWN_FUNCTION_DECLARE(NAME, SUITE) \
void NAME();\
static ::darknessNight::CppUnitTestFramework::TearDownRegister NAME##SetUpRegister =\
::darknessNight::CppUnitTestFramework::TearDownRegister(&NAME, SUITE);

#define TEARDOWN_FUNCTION(NAME, SUITE) \
TEARDOWN_FUNCTION_DECLARE(NAME, SUITE)\
void NAME()


