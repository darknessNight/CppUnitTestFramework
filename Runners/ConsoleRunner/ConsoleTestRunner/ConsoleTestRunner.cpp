// ConsoleTestRunner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ConsoleTestRunnerLibrary/TestRunnerApplication.h>

int main(int argc, const char* argv[]) {
	darknessNight::ConsoleTestRunner::TestRunnerApplication app;
	auto result= app.startProgram(argc, argv);
#ifdef _DEBUG
	std::cout << "\n\n\n";
	system("pause");
#endif
	return result;
}