#include "stdafx.h"
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight::CppUnitTestFramework::UnitTests {

	class MethodProvider {
	public:
		typedef void(MethodProvider::* Func)();
	};

	class StaticVarsContainer {
	public:
		static bool enabled;
		static MethodProvider::Func func;
	};
	bool StaticVarsContainer::enabled = false;
	MethodProvider::Func StaticVarsContainer::func;

	template <MethodProvider::Func test> class TestGetMethodFromClassTemplate {
	public:
		TestGetMethodFromClassTemplate() {
			StaticVarsContainer::func = test;
		}
	};

	class TestGetMethodFromClass {
	public:
		TestGetMethodFromClass(MethodProvider::Func func) {
			StaticVarsContainer::func = func;
		}
	};

	class TestSendOwnMethodToOtherClass :public MethodProvider {
	public:
		void reg() {
			StaticVarsContainer::enabled = true;
		}
#if (defined(_MSC_VER) && _MSC_VER>=1800)
		TestGetMethodFromClassTemplate<(MethodProvider::Func)&reg> test2;
#elif (defined (__GNUG__))
		TestGetMethodFromClass test = TestGetMethodFromClass((MethodProvider::Func)&reg);
#else
#error Not supported compiler
#endif
	};

	class TestGetName {
	public:
		const char* testName=nullptr;

		TestGetName(const char* name) {
			testName = name;
		}
	};

	class NoDefClass;
	TestGetName testOverLimits(typeid(NoDefClass).name());
	class NoDefClass {
	public:
		const char* secondNameTest = typeid(NoDefClass).name();
		TestGetName secondTest = TestGetName(secondNameTest);
	};

	TEST_CLASS(LearingAutoAddMethodTest)
	{
	public:
		TEST_METHOD(TestGetMethodFromCreatedObject) {
			TestSendOwnMethodToOtherClass test;
			std::bind(StaticVarsContainer::func, test)();//Mo¿e siê nie kompilowaæ pod GNU GCC
			Assert::IsTrue(StaticVarsContainer::enabled);
		}

		TEST_METHOD(TestGetClassNameFromNotDefClass) {
			StringAssert::Constains("CppUnitTestFramework::UnitTests::NoDefClass", testOverLimits.testName);
		}

		TEST_METHOD(TestGetClassNameInnerThisClass) {
			StringAssert::Constains("CppUnitTestFramework::UnitTests::NoDefClass", testOverLimits.testName);
		}
	};
}