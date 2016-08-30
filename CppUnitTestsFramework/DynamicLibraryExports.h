#pragma once
#include "TestsCollectionExport.h"

namespace darknessNight_CppUnitTestFramework {
	extern "C" {
#ifdef _WINNT_
		__declspec(dllexport)
#endif
		TestContainer* getTests() {
			return &TestsCollectionExport::getTestContainer();
		}
	}
}