// ConsoleTestRunner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "../TestsRunner/TestsDiscover.h"
#include "../TestsRunner/TestExecutor.h"

using namespace darknessNight::TestsRunner;
using namespace darknessNight::DependencyContainer;
using namespace darknessNight::Filesystem;
using namespace darknessNight::SharedLibrary;



int main()
{
	std::shared_ptr<Directory> dirPtr = std::make_shared<Directory>(".");
	DIContainer::Register<Directory>(dirPtr);
	DIContainer::Register<DynamicLibrary, DynamicLibrary>();

	std::cout << "Hello everybody\n";
	TestsDiscover discover;
	std::cout << "Start discover tests\n";
	discover.findAll({ "../" }, { ".dll", ".so" });
	auto result = discover.getTestsList();
	TestExecutor executor;
	std::cout << "Start running tests\n";
	auto testReports=executor.runTests(result);

	for (auto testReport : testReports) {
		std::cout << "[" << (testReport.getResult().isSuccess() ? "Success" : "Failure") << "] Cause: <"
			<< testReport.getResult().getCause() << "> Name: <" << testReport.getFullName()<<">\n";
	}

	std::cout << "\n\n\n";
	system("PAUSE");
    return 0;
}

