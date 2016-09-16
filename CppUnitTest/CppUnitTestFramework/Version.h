#pragma once
#include <string>

#define  CPPUNITTEST_LIB_VERSION_NUMBER "0.3.1.30"
#ifdef _DEBUG
#define CPPUNITTEST_LIB_CONF_LITERAL "_D";
#else
#define CPPUNITTEST_LIB_CONF_LITERAL "_S";
#endif
#define COMPILE_COUNT 1029UL

#if defined(__x86_64__) || defined(_M_X64)
#define LIB_ARCH "x64"
#elif defined(__i386) || defined(_M_IX86)
#define LIB_ARCH "x86"
#else
#define LIB_ARCH "undef"
#endif

#define CPPUNITTEST_LIBRARY_VERSION CPPUNITTEST_LIB_VERSION_NUMBER CPPUNITTEST_LIB_CONF_LITERAL
