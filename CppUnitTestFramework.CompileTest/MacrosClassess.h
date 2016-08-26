#pragma once
#include <CppUnitTestsFramework\Framework.h>



TEST_SUITE(SAME_SUITE)
TEST_SUITE_WITH_CATEGORY(SecondSuite, "Category")


TEST_CLASS_WITH_CATEGORY(TestSuiteClassOne, "Category") {
};

static int countOfArgMethods = 3;
static int testCaseCount = 4;
static std::string macrosFile = __FILE__;
static int testMethodLine = __LINE__ + 2;
TEST_CLASS(TestSuiteTestMacro) {
	TEST_METHOD(FirstTestMethod) {
		//throw exception();
	}

	ARG_TEST_METHOD(ArgMethod, 2, 4);
	ARG_TEST_METHOD(ArgMethod, 4, 4);
	ARG_TEST_METHOD(ArgMethod, 8, 4);
	void ArgMethod(int f, int s) {
	}

public:
	static bool collapseSetup;
	static bool collapseTearDown;

	SETUP_METHOD(SetUp) {
		if (collapseSetup)
			throw std::exception();
	}

	TEARDOWN_METHOD(TearDown) {
		if (collapseTearDown)
			throw std::exception();
	}
};

static bool collapseSetup = false;
static bool collapseTearDown = false;

static int testFuncLine = __LINE__ + 1;
TEST_FUNCTION_DECLARE(TestFunctionTest);


void TestFunctionTest2(int, int);
ARG_TEST_FUNCTION_IN_SUITE(TestFunctionTest2, "Unnamed", 2,2);
ARG_TEST_FUNCTION_IN_SUITE(TestFunctionTest2, "Unnamed", 2, 4);
ARG_TEST_FUNCTION(TestFunctionTest2, 2, 4);


SETUP_FUNCTION_DECLARE(SetUp, "Unnamed");

TEARDOWN_FUNCTION_DECLARE(TearDown, "Unnamed");