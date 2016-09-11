#pragma once
#include "TestsCollectionExport.h"

namespace darknessNight {
	namespace CppUnitTestFramework {

		extern "C" {
#ifdef _WIN32
			__declspec(dllexport)
#endif
				TestContainer* getTestsFromDynamicTestsLibrary() {
				return &TestsCollectionExport::getTestContainer();
			}
		}
	}
}
