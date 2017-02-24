#pragma once
#include "TestSuiteInstanceCreator.h"
#include "TestsCollectionExport.h"

namespace darknessNight {
	namespace CppUnitTestFramework {
		template<typename TestSuiteType> class TestClassWithCategoryRegister :TestRegisterContainerAccess {
		public:
			TestClassWithCategoryRegister(std::string name, TestCategory cat) {
				saveTestSuite(name, cat);
			}

			TestClassWithCategoryRegister(TestCategory cat) {
				std::string name = getClassName<TestSuiteType>();
				saveTestSuite(name, cat);
			}
		private:

			void saveTestSuite(std::string& name, TestCategory& cat) {
				std::shared_ptr<TestSuiteCreator> testSuite(new TestSuiteInstanceCreator<TestSuiteType>(name, cat));
				getTestContainer().addTestSuite(testSuite);
			}
		};
	}
}