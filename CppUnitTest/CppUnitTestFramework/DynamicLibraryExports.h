#pragma once
#include "TestsCollectionExport.h"

namespace darknessNight {
	namespace CppUnitTestFramework {

#ifdef _WIN32
			__declspec(dllexport)
#endif
extern "C" {
				TestContainer* getTestsFromDynamicTestsLibrary() {
				return &TestsCollectionExport::getTestContainer();
			}
		}
	}
}
