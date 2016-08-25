#pragma once
#include "TestSuiteInstanceCreator.h"
#include "TestsCollectionExport.h"

namespace darknessNight::CppUnitTestFramework {
	template<typename TestSuiteType> class TestClassWithCategoryRegister :TestRegisterContainerAccess {
	public:
		TestClassWithCategoryRegister(string name, TestCategory cat) {
			saveTestSuite(name);
		}

		TestClassWithCategoryRegister(TestCategory cat) {
			string name = getClassName<TestSuiteType>();
			saveTestSuite(name);
		}
	private:

		void saveTestSuite(string name) {
			shared_ptr<TestSuiteCreator> testSuite(new TestSuiteInstanceCreator<TestSuiteType>(name));
			getTestContainer().addTestSuite(testSuite);
		}
	};
}