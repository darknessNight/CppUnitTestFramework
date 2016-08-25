#pragma once
#include "CppUnitTestFramework.CompileTest.h"

const darknessNight::CppUnitTestFramework::TestReport getTestRaport(std::string & suite, std::string & funcName);
void checkCorrectRemeberFileAndLine(std::string &suite, std::string &funcName, std::string &file, int funcLine);
void checkCorrectRememberLine(darknessNight::CppUnitTestFramework::TestReport report, int funcLine);
void checkCorrectRemeberFile(darknessNight::CppUnitTestFramework::TestReport report, std::string & file);
void checkTestSuiteHasMethod(std::string &suite, std::string &funcName);
std::vector<string> getTestCaseListFromSuite(std::string &suite);

