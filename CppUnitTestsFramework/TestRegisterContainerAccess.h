#pragma once
#include "TestsCollectionExport.h"

namespace darknessNight::CppUnitTestFramework {
	class TestRegisterContainerAccess {
	protected:
		TestRegisterContainerAccess() {}
		TestSuitePtr getTestSuite(std::string &testSuite) {
			auto suite = TestsCollectionExport::getTestContainer().getTestSuiteByName(testSuite);
			return suite;
		}

		TestContainer& getTestContainer() {
			return TestsCollectionExport::getTestContainer();
		}
	};
}