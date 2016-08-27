#pragma once
#include "EqualAssert.h"
#include "GreaterLessAssert.h"
#include "AssertBoolean.h"
#include "AssertExceptionCatcher.h"

namespace darknessNight_CppUnitTestFramework {
	class Assert: public AssertEqual, public AssertGreaterLess, public AssertBoolean, public AssertExceptionCatcher{
	};
}