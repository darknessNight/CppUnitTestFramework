#pragma once
#include "TestsCollectionExport.h"

namespace darknessNight {
	namespace CppUnitTestFramework {

#ifdef _WIN32
extern "C" {
			__declspec(dllexport)
#endif
				TestContainer* getTestsFromDynamicTestsLibrary() {
				return &TestsCollectionExport::getTestContainer();
			}
#ifdef _WIN32
		}
#endif
	}
}
