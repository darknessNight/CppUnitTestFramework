#pragma once
#include "TestContainer.h"
#include "TestSuiteInstanceCreator.h"

namespace darknessNight::CppUnitTestFramework {
	class TestsCollectionExport {
	private:
		static std::unique_ptr<TestContainer> suiteContainer;
	public:
		static TestContainer& getTestContainer() {
			createContainerIfNeeded();
			return *suiteContainer;
		}

		static void clear() {
			suiteContainer = nullptr;
		}

		static void discoverTest() {
			throw exception();
		}

	private:
		static void createContainerIfNeeded()
		{
			if (suiteContainer == nullptr)
				suiteContainer = std::unique_ptr<TestContainer>(new TestContainer);
		}
	};
}