// ConsoleTestRunner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "../TestsRunner/TestsDiscover.h"
#include "../TestsRunner/TestExecutor.h"
#include "ConsoleTestRunner.h"

using namespace darknessNight::TestsRunner;
using namespace darknessNight::Filesystem;
using namespace darknessNight::SharedLibrary;
using namespace std;



int main() {
	std::shared_ptr<Directory> dirPtr = std::make_shared<Directory>(".");
	auto dynamicLibraries = std::make_shared<DynamicLibrary>();
	TestSuite::TestReportArray testReports;

	{
		std::cout << "Hello everybody\n";
		TestsDiscover discover(dirPtr,dynamicLibraries);
		std::cout << "Start discover tests\n";
		discover.findAll({ "../" }, { ".dll", ".so" });
		std::cout << "I founded it!";
		auto result = discover.getTestsList();
		TestExecutor executor(dirPtr, dynamicLibraries);
		std::cout << "Start running tests\n";
		testReports = executor.runTests(result);
	}

	dynamicLibraries->freeAllLibraries();

	int passing = 0, falling = 0;
	for (auto testReport : testReports) {
		std::cout << "[" << (testReport.getResult().isSuccess() ? "Success" : "Failure") << "] Cause: <"
			<< testReport.getResult().getCause() << "> Name: <" << testReport.getFullName() << ">";
		if (testReport.getResult().isFailure())
			std::cout << "Error: <" << testReport.getResult().getErrorMessage() << ">";
		std::cout << " Duration: <" << std::chrono::duration_cast<std::chrono::milliseconds>(testReport.getResult().getDurationTime()).count() << "ms>\n";
		if (testReport.getResult().isSuccess())
			passing++;
		else falling++;
	}

	std::cout << "\n\nPassing tests: " << passing << "\nFalling tests: " << falling;

#ifdef _DEBUG
	std::cout << "\n\n\n";
	std::system("PAUSE");
#endif
	if (falling)
		return 1;
	return 0;
}

