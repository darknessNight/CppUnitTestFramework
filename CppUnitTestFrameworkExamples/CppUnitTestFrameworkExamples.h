// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CPPUNITTESTFRAMEWORKEXAMPLES_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CPPUNITTESTFRAMEWORKEXAMPLES_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CPPUNITTESTFRAMEWORKEXAMPLES_EXPORTS
#define CPPUNITTESTFRAMEWORKEXAMPLES_API __declspec(dllexport)
#else
#define CPPUNITTESTFRAMEWORKEXAMPLES_API __declspec(dllimport)
#endif

// This class is exported from the CppUnitTestFrameworkExamples.dll
class CPPUNITTESTFRAMEWORKEXAMPLES_API CCppUnitTestFrameworkExamples {
public:
	CCppUnitTestFrameworkExamples(void);
	// TODO: add your methods here.
};

extern CPPUNITTESTFRAMEWORKEXAMPLES_API int nCppUnitTestFrameworkExamples;

CPPUNITTESTFRAMEWORKEXAMPLES_API int fnCppUnitTestFrameworkExamples(void);
