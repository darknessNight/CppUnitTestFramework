// ConsoleTestRunner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
#ifdef _WIN32
	auto module = LoadLibrary(L"CppUnitTestFrameworkExamples.dll");
	if (module == nullptr)
		std::cout << "Failed load library";
	else {
		auto func = GetProcAddress(module, "getTests");
		if (func == nullptr)
			std::cout << "Failed load get tests func";
		else std::cout << "Success";
		FreeLibrary(module);
	}
	std::cout << "\n\n\n";
	system("PAUSE");
#endif
#ifdef __linux
	std::cout << "Linux not yet supported";
#endif
    return 0;
}

