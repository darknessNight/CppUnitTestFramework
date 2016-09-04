#pragma once
#include "CppUnitTestFramework.CompileTest.h"

void checkTestFuncNotFalling(darknessNight::CppUnitTestFramework::TestSuitePtr &testSuite);
void checkRegisterTearDown(darknessNight::CppUnitTestFramework::TestSuitePtr &testSuite);
const std::vector<darknessNight::CppUnitTestFramework::TestReport> actRunTearDown(darknessNight::CppUnitTestFramework::TestSuitePtr & testSuite);
void checkRegisterSetUp(darknessNight::CppUnitTestFramework::TestSuitePtr &testSuite);
std::vector<darknessNight::CppUnitTestFramework::TestReport> actRunSetUpMethod(darknessNight::CppUnitTestFramework::TestSuitePtr & testSuite);
void assertRegisterSetUp(std::vector<darknessNight::CppUnitTestFramework::TestReport> &results);
void assertRegisterTearDown(std::vector<darknessNight::CppUnitTestFramework::TestReport> &results);
