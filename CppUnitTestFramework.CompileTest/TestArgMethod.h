#pragma once
#include "stdafx.h"

const std::vector<std::string> getTestCasesList();

int findArgMethods(std::vector<std::string> &testCases, std::string &samplename);

void checkArgMethodName(std::string test, int & count, std::string & samplename);

void checkHasCorrectArgMethodCount(int count);

void checkHasCorrectArgMethodName(std::string &samplename);

bool noHasArgsInName(std::string & samplename);
