#include "stdafx.h"
#include "../DependencyContainer/DependencyContainer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {
	namespace DependencyContainer {
		namespace Tests {
			__interface FakeInterface {
public:
	bool OneMethod();
			};

			class FakeInstance :public FakeInterface {
			private:
				int e = 0;
			public:
				FakeInstance(int i) {
					e = i;
				}
				FakeInstance() :FakeInstance(0) {}

				bool OneMethod() {
					return true;
				}
			};

			TEST_CLASS(DependencyCointainerTests) {
			public:

				TEST_METHOD_INITIALIZE(SetUp) {
					DIContainer::clear();
				}

				TEST_METHOD(AddType_HasPointer_CheckSave) {
					try {
						DIContainer::Register<FakeInterface>(std::make_shared<FakeInstance>());
						auto result = DIContainer::Get<FakeInterface>();
						Assert::IsFalse(result==nullptr);
						Assert::IsTrue(result->OneMethod());
					}
					catch (...) {
						Assert::Fail();
					}
				}

				TEST_METHOD(AddType_HasType_CheckSave) {
					try {
						DIContainer::Register<FakeInterface, FakeInstance>();
						auto result = DIContainer::Get<FakeInterface>();
						Assert::IsFalse(result == nullptr);
						Assert::IsTrue(result->OneMethod());
					}
					catch (...) {
						Assert::Fail();
					}
				}

			};
		}
	}
}