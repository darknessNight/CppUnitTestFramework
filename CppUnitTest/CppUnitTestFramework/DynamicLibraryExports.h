#pragma once
#include "TestsCollectionExport.h"
#include "Version.h"

namespace darknessNight {
	namespace CppUnitTestFramework {

		extern "C" {
#ifdef _WIN32
			__declspec(dllexport)
#endif
				const char* getTestLibVersion() {
				return CPPUNITTEST_LIBRARY_VERSION;
			}
#ifdef _WIN32
			__declspec(dllexport)
#endif
				TestContainer* getTestsFromDynamicTestsLibrary() {
				return &TestsCollectionExport::getTestContainer();
			}
		}
	}
}
