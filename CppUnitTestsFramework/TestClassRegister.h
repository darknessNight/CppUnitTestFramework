#pragma once
#include "TestSuiteInstanceCreator.h"
#include "TestsCollectionExport.h"

namespace darknessNight::CppUnitTestFramework {
	template<typename TestSuiteType> class TestClassRegister:TestRegisterContainerAccess {
	public:
		TestClassRegister(string name) {
			saveTestSuite(name);
		}

		TestClassRegister() {
			string name=detectClassName();
			saveTestSuite(name);
		}
	private:
		string detectClassName()
		{
			string name = typeid(TestSuiteType).name();
			name = name.substr(strlen("class "));
			return name;
		}

		void saveTestSuite(string name) {
			shared_ptr<TestSuiteCreator> testSuite(new TestSuiteInstanceCreator<TestSuiteType>(name));
			getTestContainer().addTestSuite(testSuite);
		}
	};
}