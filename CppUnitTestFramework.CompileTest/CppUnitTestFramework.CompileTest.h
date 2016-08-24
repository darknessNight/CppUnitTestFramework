#include <string>

using namespace std;

void testTestCaseMacro(string suite, string funcName, string file, int funcLine);
void testFunctionMacro();
void showError(void(*)());
void testClassAndMethodMacro();
void testClassSetUpAndTearDown();

void writeTestResult(string,void(*)());

class SpecialException {
private:
	string message;
public:
	SpecialException(string mess) {
		message = mess;
	}

	string what() {
		return message;
	}
};