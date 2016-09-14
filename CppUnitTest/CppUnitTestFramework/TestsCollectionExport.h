#pragma once
#include "TestContainer.h"
#include "TestSuiteInstanceCreator.h"
#include "HelperFuncs.h"

namespace darknessNight {
	namespace CppUnitTestFramework {
		class TestsCollectionExport {
		private:
			//static std::unique_ptr<TestContainer> suiteContainer;
		public:
			static TestContainer& getTestContainer() {
				static TestContainer suiteContainer;
				return suiteContainer;
			}

			static void discoverTest() {
				throw exception();
			}

		private:
			static void createContainerIfNeeded() {
				/*if (suiteContainer == nullptr)
					suiteContainer = std::unique_ptr<TestContainer>(new TestContainer);*/
			}
		};
	}
}