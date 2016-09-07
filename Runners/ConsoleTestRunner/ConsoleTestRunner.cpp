// ConsoleTestRunner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../TestsRunner/TestsDiscover.h"
#include "../TestsRunner/TestExecutor.h"

using namespace darknessNight::TestsRunner;

int main()
{
	TestsDiscover discover;
	discover.findAll({ "." }, { ".dll" });
	auto result = discover.getTestsList();
	TestExecutor executor;
	auto testReports=executor.runTests(result);

	for (auto testReport : testReports) {
		std::cout << "[" << (testReport.getResult().isSuccess() ? "Success" : "Failure") << " Cause: "
			<< testReport.getResult().getCause() << " Name: " << testReport.getFullName();
	}

	std::cout << "\n\n\n";
	system("PAUSE");
    return 0;
}

