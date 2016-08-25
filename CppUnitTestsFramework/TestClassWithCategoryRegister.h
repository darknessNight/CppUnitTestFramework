#pragma once
#include "TestSuiteInstanceCreator.h"
#include "TestsCollectionExport.h"

namespace darknessNight::CppUnitTestFramework {
	template<typename TestSuiteType> class TestClassWithCategoryRegister :TestRegisterContainerAccess {
	public:
		TestClassWithCategoryRegister(string name, TestCategory cat) {
			saveTestSuite(name, cat);
		}

		TestClassWithCategoryRegister(TestCategory cat) {
			string name = getClassName<TestSuiteType>();
			saveTestSuite(name, cat);
		}
	private:

		void saveTestSuite(string& name, TestCategory& cat) {
			shared_ptr<TestSuiteCreator> testSuite(new TestSuiteInstanceCreator<TestSuiteType>(name, cat));
			getTestContainer().addTestSuite(testSuite);
		}
	};
}