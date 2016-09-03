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
			public:
				bool OneMethod() {
					return true;
				}
			};

			TEST_CLASS(DependencyCointainerTests) {
			public:

				TEST_METHOD_INITIALIZE(SetUp) {
					DependencyContainer::clear();
				}

				TEST_METHOD(AddType_HasPointer_CheckSave) {
					try {
						DependencyContainer::Register<FakeInterface>(std::make_shared<FakeInstance>());
						auto result = DependencyContainer::Get<FakeInterface>();
						Assert::IsFalse(result==nullptr);
						Assert::IsTrue(result->OneMethod());
					}
					catch (...) {
						Assert::Fail();
					}
				}

				TEST_METHOD(AddType_HasType_CheckSave) {
					try {
						DependencyContainer::Register<FakeInterface, FakeInstance>();
						auto result = DependencyContainer::Get<FakeInterface>();
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