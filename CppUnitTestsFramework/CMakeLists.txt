cmake_minimum_required (VERSION 2.6)
project (CppUnitTestFramework)
	add_library(CppUnitTestFramework AssertExceptionCatcher.cpp AssertHelper.cpp BasicAssert.cpp FunctionTester.cpp HelperFuncs.cpp TestCase.cpp TestCategory.cpp TestContainer.cpp TestRegisterer.cpp TestReport.cpp TestResult.cpp TestSuite.cpp TestSuiteCreator.cpp ToStringConverter.cpp)
