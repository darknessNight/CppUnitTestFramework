#pragma once
#include "TestCategory.h"
#include "TestResult.h"
namespace darknessNight_CppUnitTestFramework {
	class TestReport {
	private:
		TestResult testResult;
		std::string testName;
		std::string testFile;
		unsigned testLine;
		std::string testSuite;
		TestCategory testCategory;
		friend class TestCase;
	private:
		TestReport();
	public:
		TestResult getResult();
		std::string getTestName();
		std::string getFile();
		unsigned getLine();
		std::string getSuiteName();
		TestCategory getCategory();
	};
}