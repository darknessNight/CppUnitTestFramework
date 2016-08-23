#pragma once
#include "TestSuiteInstanceCreator.h"
#include "TestsCollectionExport.h"

namespace darknessNight::CppUnitTestFramework {
	template<typename TestSuiteType> class TestClassRegister {
	public:
		TestClassRegister(std::string name) {
			std::shared_ptr<TestSuiteCreator> testSuite(new TestSuiteInstanceCreator<TestSuiteType>(name.substr(strlen("class "))));
			TestsCollectionExport::getTestContainer().addTestSuite(testSuite);
		}
	};
}