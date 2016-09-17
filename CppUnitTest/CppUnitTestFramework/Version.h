#pragma once
#include <string>

#define  CPPUNITTEST_LIB_VERSION_NUMBER "0.3.2.8"
#ifdef _DEBUG
#define CPPUNITTEST_LIB_CONF_LITERAL "Debug";
#else
#define CPPUNITTEST_LIB_CONF_LITERAL "Static";
#endif
#define COMPILE_COUNT 1058UL

#if defined(__x86_64__) || defined(_M_X64)
#define LIB_ARCH "x64"
#elif defined(__i386) || defined(_M_IX86)
#define LIB_ARCH "x86"
#else
#define LIB_ARCH "undef"
#endif

#define CPPUNITTEST_LIBRARY_VERSION CPPUNITTEST_LIB_VERSION_NUMBER "_" CPPUNITTEST_LIB_CONF_LITERAL "_" LIB_ARCH
