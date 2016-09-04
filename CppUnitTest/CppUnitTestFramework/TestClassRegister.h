#pragma once
#include "TestSuiteInstanceCreator.h"
#include "TestsCollectionExport.h"

namespace darknessNight {
	namespace CppUnitTestFramework {
		template<typename TestSuiteType> class TestClassRegister :TestRegisterContainerAccess {
		public:
			TestClassRegister(std::string name) {
				saveTestSuite(name);
			}

			TestClassRegister() {
				std::string name = getClassName<TestSuiteType>();
				saveTestSuite(name);
			}
		private:

			void saveTestSuite(std::string name) {
				if(typeid(TestSuiteType)==typeid(TestSuite))
					std::shared_ptr<TestSuiteCreator> testSuite(new TestSuiteCreator(name));
				else std::shared_ptr<TestSuiteCreator> testSuite(new TestSuiteInstanceCreator<TestSuiteType>(name));
				getTestContainer().addTestSuite(testSuite);
			}
		};
	}
}