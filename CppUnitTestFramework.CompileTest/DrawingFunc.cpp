#include "CppUnitTestFramework.CompileTest.h"
#include <CppUnitTestsFramework\Framework.h>
#include <iostream>
#include <string>


using namespace darknessNight_CppUnitTestFramework;

void drawLineTest() {
	std::cout << "\n===========================================================================\n\n";
}
void drawLineHeader() {
	std::cout << "\n---------------------------------------------------------------------------\n";
}

void writeTestResult(std::string text, void(*func)())
{
	std::cout << text;
	drawLineHeader();
	showError(func);
	drawLineTest();
}

void showError(void(*func)()) {
	try {
		func();
	}
	catch (SpecialException ex) {
		std::cout << ex.what() << "\n";
	}
	catch (NotFoundException ex) {
		std::cout << "Not register test class\n";
		std::cout << "Exception message: " << ex.what() << "\n";
	}
	catch (TestRegisterException ex) {
		std::cout << "Register method exception\n";
		std::cout << "Exception message: " << ex.what() << "\n";
	}
	catch (darknessNight_CppUnitTestFramework::exception ex) {
		std::cout << "Catched exception: " << ex.what() << "\n";
	}
	catch (std::exception ex) {
		std::cout << "Catched native exception: " << ex.what() << "\n";
	}
	catch (...) {
		std::cout << "Unknow error" << "\n";
	}
}