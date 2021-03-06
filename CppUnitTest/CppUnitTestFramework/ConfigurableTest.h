#pragma once
#include <memory>
#include <functional>

namespace darknessNight {
	namespace CppUnitTestFramework {
		class ConfigurableTest {
		public:
			typedef void (ConfigurableTest::*TestMethod)();
		protected:
			std::function<void()> setUpMethod;
			std::function<void()> tearDownMethod;

		protected:
			virtual void setUp() {
				if (setUpMethod != nullptr)
					setUpMethod();
			}

			virtual void tearDown() {
				if (tearDownMethod != nullptr)
					tearDownMethod();
			}
		public:
			virtual void setSetUpMethod(std::function<void()> func) {
				setUpMethod = func;
			}

			virtual void setTearDownMethod(std::function<void()> func) {
				tearDownMethod = func;
			}
		};
		typedef std::shared_ptr<ConfigurableTest> ConfigurableTestPtr;
	}
}
