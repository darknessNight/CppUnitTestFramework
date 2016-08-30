// CppUnitTestFrameworkExamples.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CppUnitTestFrameworkExamples.h"


// This is an example of an exported variable
CPPUNITTESTFRAMEWORKEXAMPLES_API int nCppUnitTestFrameworkExamples=0;

// This is an example of an exported function.
CPPUNITTESTFRAMEWORKEXAMPLES_API int fnCppUnitTestFrameworkExamples(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see CppUnitTestFrameworkExamples.h for the class definition
CCppUnitTestFrameworkExamples::CCppUnitTestFrameworkExamples()
{
    return;
}
