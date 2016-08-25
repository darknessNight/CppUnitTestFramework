#include "MacrosClassess.h"


bool TestSuiteTestMacro::collapseSetup = false;
bool TestSuiteTestMacro::collapseTearDown = false;

void TestFunctionTest() {
}

void SetUp() {
	if (collapseSetup)
		throw exception();
}

 void TearDown(){
 if (collapseTearDown)
	 throw exception();
}