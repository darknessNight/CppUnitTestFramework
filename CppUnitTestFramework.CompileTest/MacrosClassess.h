#pragma once
#include <CppUnitTestsFramework\Framework.h>



TEST_SUITE(SAME_SUITE)
TEST_SUITE_WITH_CATEGORY(SecondSuite, "Category")


TEST_CLASS_WITH_CATEGORY(TestSuiteClassOne, "Category") {
};

static string macrosFile = __FILE__;
static int testMethodLine = __LINE__ + 2;
TEST_CLASS(TestSuiteTestMacro) {
	TEST_METHOD(FirstTestMethod) {
		//throw exception();
	}

public:
	static bool collapseSetup;
	static bool collapseTearDown;

	SETUP_METHOD(SetUp) {
		if (collapseSetup)
			throw exception();
	}

	TEARDOWN_METHOD(TearDown) {
		if (collapseTearDown)
			throw exception();
	}
};

static bool collapseSetup = false;
static bool collapseTearDown = false;

static int testFuncLine = __LINE__ + 1;
TEST_FUNCTION(TestFunctionTest);

SETUP_FUNCTION(SetUp, "Unnamed");

TEARDOWN_FUNCTION(TearDown, "Unnamed");