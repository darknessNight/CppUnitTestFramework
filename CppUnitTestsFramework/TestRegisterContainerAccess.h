#pragma once
#include "TestsCollectionExport.h"
#include "Exceptions.h"

namespace darknessNight::CppUnitTestFramework {
	class TestRegisterContainerAccess {
	protected:
		TestRegisterContainerAccess() {}
		TestSuitePtr getTestSuite(std::string testSuite) {
			try {
				return TestsCollectionExport::getTestContainer().getTestSuiteByName(testSuite); 
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