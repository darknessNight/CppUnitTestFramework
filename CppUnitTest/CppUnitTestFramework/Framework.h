#pragma once
#include "SuiteMacros.h"
#include "FuncMacros.h"
#include "MethodMacros.h"
#include "ConfMacros.h"
#include "Assert.h"


#if (!defined(_MSC_VER) && __cplusplus<201103L) || (defined(_MSC_VER) && _MSC_VER<=1700)
#error Required C++11 copability compiler
#endif

