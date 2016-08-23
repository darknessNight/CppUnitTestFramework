#pragma once
#include "TestsCollectionExport.h"

namespace darknessNight::CppUnitTestFramework {
	class TestCaseRegister {
	protected:
		TestCaseRegister() {}
		TestSuitePtr getTestSuite(std::string &testSuite) {
			auto suite = TestsCollectionExport::getTestContainer().getTestSuiteByName(testSuite);
			return suite;
		}
	};
}