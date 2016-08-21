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
		TestReport() :testResult(false) {}
	public:
		TestResult getResult() {
			return testResult;
		}

		string getTestName() {
			return "TestName";
		}

		string getFile() {
			return testFile;
		}

		unsigned getLine() {
			return testLine;
		}

		string getSuite() {
			return testSuite;
		}

		TestCategory getCategory() {
			return testCategory;
		}
	};
}