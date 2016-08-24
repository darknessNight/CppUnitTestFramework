#pragma once
#include "TestsCollectionExport.h"

namespace darknessNight::CppUnitTestFramework {
	class TestRegisterContainerAccess {
	protected:
		TestRegisterContainerAccess() {}
		TestSuitePtr getTestSuite(std::string testSuite) {
			try {
				auto suite = TestsCollectionExport::getTestContainer().getTestSuiteByName(testSuite);
				return suite;
			}
			catch (NotFoundException ex) {
				throw TestRegisterException(ex.what());
			}
		}

		TestContainer& getTestContainer() {
			return TestsCollectionExport::getTestContainer();
		}
	};
}