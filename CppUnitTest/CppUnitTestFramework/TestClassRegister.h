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
				std::shared_ptr<TestSuiteCreator> testSuite;
				if (typeid(TestSuiteType) == typeid(TestSuite))
					testSuite = std::shared_ptr<TestSuiteCreator>(new TestSuiteCreator(name));
				else
					testSuite = std::shared_ptr<TestSuiteCreator>(new TestSuiteInstanceCreator<TestSuiteType>(name));
				getTestContainer().addTestSuite(testSuite);
			}
		};
	}
}