#pragma once
#include "TestsCollectionExport.h"

namespace darknessNight_CppUnitTestFramework {
	extern "C" {
#ifdef _WIN32
		__declspec(dllexport)
#endif
		TestContainer* getTests() {
			return &TestsCollectionExport::getTestContainer();
		}
	}
}