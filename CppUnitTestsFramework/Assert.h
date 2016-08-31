#pragma once
#include "EqualAssert.h"
#include "GreaterLessAssert.h"
#include "AssertBoolean.h"
#include "AssertExceptionCatcher.h"
#include "AssertString.h"
#include "AssertArray.h"

namespace darknessNight{namespace CppUnitTestFramework {
	class Assert: public AssertEqual, public AssertGreaterLess, public AssertBoolean, public AssertExceptionCatcher{
	public:
		typedef AssertEqual Equal;
		typedef AssertExceptionCatcher Exception;
		typedef AssertGreaterLess GreaterLess;
		typedef AssertBoolean Bool;
		typedef AssertString String;
		typedef AssertArray Array;
	};
}}