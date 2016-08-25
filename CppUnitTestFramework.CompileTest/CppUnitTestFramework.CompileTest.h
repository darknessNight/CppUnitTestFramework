#include <string>
#include <vector>
#include <iostream>
#include "MacrosClassess.h"



void testTestCaseMacro(std::string suite, std::string funcName, std::string file, int funcLine);
void testFunctionMacro();
void showError(void(*)());
void testClassAndMethodMacro();
void testClassSetUpAndTearDown();

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