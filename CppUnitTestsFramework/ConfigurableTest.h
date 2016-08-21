#pragma once
#include <memory>
namespace darknessNight::CppUnitTestFramework {
	class ConfigurableTest abstract {
	public:
		typedef void (ConfigurableTest::*TestMethod)();
	protected:
		virtual void setUp() {
		}
		virtual void tearDown() {
		}
	};
	typedef std::shared_ptr<ConfigurableTest> ConfigurableTestPtr;
}