// ConsoleTestRunner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>

int main()
{
	auto module = LoadLibrary(L"CppUnitTestFrameworkExamples.dll");
	if (module == nullptr)
		std::cout << "Failed load library";
	else {
		auto func = GetProcAddress(module, "getTests");
		if (func == nullptr)
			std::cout << "Failed load get tests func";
		else std::cout << "Success";
	}
	std::cout << "\n\n\n";
	system("PAUSE");
    return 0;
}

