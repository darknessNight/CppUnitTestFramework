#pragma once
#include "CppUnitTestFramework.CompileTest.h"

const darknessNight_CppUnitTestFramework::TestReport getTestRaport(std::string & suite, std::string & funcName);
void checkCorrectRemeberFileAndLine(std::string &suite, std::string &funcName, std::string &file, int funcLine);
void checkCorrectRememberLine(darknessNight_CppUnitTestFramework::TestReport report, int funcLine);
void checkCorrectRemeberFile(darknessNight_CppUnitTestFramework::TestReport report, std::string & file);
void checkTestSuiteHasMethod(std::string &suite, std::string &funcName);
std::vector<std::string> getTestCaseListFromSuite(std::string &suite);

