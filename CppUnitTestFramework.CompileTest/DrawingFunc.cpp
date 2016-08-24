#include "CppUnitTestFramework.CompileTest.h"
#include <CppUnitTestsFramework\Framework.h>
#include <iostream>
#include <string>

using namespace std;
using namespace darknessNight::CppUnitTestFramework;

void drawLineTest() {
	cout << "\n===========================================================================\n\n";
}
void drawLineHeader() {
	cout << "\n---------------------------------------------------------------------------\n";
}

void writeTestResult(string text, void(*func)())
{
	cout << text;
	drawLineHeader();
	showError(func);
	drawLineTest();
}

void showError(void(*func)()) {
	try {
		func();
	}
	catch (SpecialException ex) {
		cout << ex.what() << "\n";
	}
	catch (NotFoundException ex) {
		cout << "Not register test class\n";
		cout << "Exception message: " << ex.what() << "\n";
	}
	catch (TestRegisterException ex) {
		cout << "Register method exception\n";
		cout << "Exception message: " << ex.what() << "\n";
	}
	catch (exception ex) {
		cout << "Catched exception: " << ex.what() << "\n";
	}
	catch (...) {
		cout << "Unknow error" << "\n";
	}
}