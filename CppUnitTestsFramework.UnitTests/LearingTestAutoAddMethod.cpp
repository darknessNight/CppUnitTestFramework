#include "stdafx.h"
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight::CppUnitTestFramework::UnitTests {
	class MasterTest {
	public:
		typedef void(MasterTest::* Func)();
	};

	class TestStaticMaster {
	public:
		static bool enabled;
		static MasterTest::Func func;
	};
	bool TestStaticMaster::enabled = false;
	MasterTest::Func TestStaticMaster::func;

	template <MasterTest::Func test> class TestStatic {
	public:
		TestStatic() {
			TestStaticMaster::func = test;
		}
	};

	class Test3 {
	public:
		Test3(MasterTest::Func func) {
			TestStaticMaster::func = func;
		}
	};

	class Test2 :public MasterTest {
	public:
		void reg() {
			TestStaticMaster::enabled = true;
		}

#if (defined(_MSC_VER) && _MSC_VER>=1800)
		TestStatic<(MasterTest::Func)&reg> test2;
#elif (defined (__GNUG__))
		Test3 test = Test3((MasterTest::Func)&reg);
#else
#error Not supported compiler
#endif
	};

	TEST_CLASS(LearingAutoAddMethodTest)
	{
	public:
		TEST_METHOD(Test) {
			Test2 test;
			std::bind(TestStaticMaster::func, test)();
			Assert::IsTrue(TestStaticMaster::enabled);
		}
	};
}