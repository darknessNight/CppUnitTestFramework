#pragma once
#include "TestCategory.h"
#include "TestResult.h"
namespace darknessNight {
	namespace CppUnitTestFramework {
		class TestReport {
		protected:
			TestResult testResult;
			std::string testName;
			std::string testFile;
			unsigned testLine;
			std::string testSuite;
			TestCategory testCategory;
			friend class TestCase;
		protected:
			TestReport();
		public:
			TestResult& getResult();
			std::string getTestName();
			std::string getFile();
			std::string getFullName();
			unsigned getLine();
			std::string getSuiteName();
			TestCategory getCategory();
		};
	}
}