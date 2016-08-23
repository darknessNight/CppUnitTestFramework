#pragma once
#include "TestContainer.h"
#include "TestSuiteInstanceCreator.h"

namespace darknessNight::CppUnitTestFramework {
	class TestsCollectionExport {
	private:
		static std::unique_ptr<TestContainer> suiteContainer;
	public:
		static TestContainer& getTestContainer() {
			if (suiteContainer == nullptr)
				suiteContainer = std::unique_ptr<TestContainer>(new TestContainer);
			return *suiteContainer;
		}

		static void discoverTest() {
			throw exception();
		}
	};
}