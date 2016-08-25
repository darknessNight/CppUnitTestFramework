#pragma once
#include "CppUnitTestFramework.CompileTest.h"

void checkTestFuncNotFalling(darknessNight_CppUnitTestFramework::TestSuitePtr &testSuite);
void checkRegisterTearDown(darknessNight_CppUnitTestFramework::TestSuitePtr &testSuite);
const std::vector<darknessNight_CppUnitTestFramework::TestReport> actRunTearDown(darknessNight_CppUnitTestFramework::TestSuitePtr & testSuite);
void checkRegisterSetUp(darknessNight_CppUnitTestFramework::TestSuitePtr &testSuite);
std::vector<darknessNight_CppUnitTestFramework::TestReport> actRunSetUpMethod(darknessNight_CppUnitTestFramework::TestSuitePtr & testSuite);
void assertRegisterSetUp(std::vector<darknessNight_CppUnitTestFramework::TestReport> &results);
void assertRegisterTearDown(std::vector<darknessNight_CppUnitTestFramework::TestReport> &results);
