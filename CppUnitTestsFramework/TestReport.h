#pragma once
#include "TestCategory.h"
#include "TestResult.h"
namespace darknessNight::CppUnitTestFramework {
	class TestReport {
	private:
		TestResult testResult;
		string testName;
		string testFile;
		unsigned testLine;
		string testSuite;
		TestCategory testCategory;
		friend class TestCase;
	private:
		TestReport();
	public:
		TestResult getResult();
		string getTestName();
		string getFile();
		unsigned getLine();
		string getSuiteName();
		TestCategory getCategory();
	};
}