#pragma once
#include <functional>
#include <string>

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
		string testName = "";

		TestGetName(string name) {
			testName = name;
		}
	};




	class NoDefClass;
	TestGetName testOverLimits(typeid(NoDefClass).name());
	class NoDefClass {
	public:
		string secondNameTest = typeid(NoDefClass).name();
		TestGetName secondTest = TestGetName(secondNameTest);
	};


}