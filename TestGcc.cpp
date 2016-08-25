#include <iostream>
#include<functional>
	class MasterTest {
	public:
		typedef void(MasterTest::*Func)();
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

        std::function<void()> func=[=](){this->reg();};

		void reg() {
			TestStaticMaster::enabled = true;
		}
	};

#if (!defined(_MSC_VER) && __cplusplus<201103L) || (defined(_MSC_VER) && _MSC_VER<=1700)
#error Required C++11 copability compiler
#endif

	int main(){

			Test2 test;
			//std::bind(TestStaticMaster::func, test)();
			std::cout<<__cplusplus<<std::endl;
            test.func();
			std::cout<<(TestStaticMaster::enabled?"Success":"Failed");
			return 0;
    }
