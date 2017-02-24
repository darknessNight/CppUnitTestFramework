#include <string>
#include <vector>
#include <iostream>
#include "MacrosClassess.h"
#include "stdafx.h"



void testTestCaseMacro(int testCaseCount, std::string suite, std::string funcName, std::string file, int funcLine);
void testFunctionMacro();
void showError(void(*)());
void testClassAndMethodMacro();
void checkIsCorrectSuitesCount();
void testClassSetUpAndTearDown();
void testArgMethodAndFunc();
void testIgnoreMethod();
void writeTestResult(std::string,void(*)());



class SpecialException {
private:
	std::string message;
public:
	SpecialException(std::string mess) {
		message = mess;
	}

	std::string what() {
		return message;
	}
};
