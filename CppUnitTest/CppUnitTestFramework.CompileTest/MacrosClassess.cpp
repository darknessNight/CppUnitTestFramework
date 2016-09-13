#include "MacrosClassess.h"


bool TestSuiteTestMacro::collapseSetup = false;
bool TestSuiteTestMacro::collapseTearDown = false;

void TestFunctionTest() {
}

class exception:public std::exception{
private:
    std::string message;
public:
    exception(std::string mess){
        message=mess;
    }
    const char* what(){
        return message.c_str();
    }
};

void SetUp() {
	if (collapseSetup)
		throw std::exception("SetUp not catched exception");
}

 void TearDown(){
 if (collapseTearDown)
	 throw std::exception("TearDown not catched exception");
}

 void TestFunctionTest2(int, int)
 {
 }
