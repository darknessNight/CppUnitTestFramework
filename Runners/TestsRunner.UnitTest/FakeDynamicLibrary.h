#pragma once
#include "../TestsRunner/Filesystem/Directory.h"
#include "../TestsRunner/SharedLibrary.h"
#include <CppUnitTestFramework/TestContainer.h>
#include <CppUnitTestFramework/Version.h>

using namespace darknessNight::Filesystem;
using namespace darknessNight::SharedLibrary;
using namespace darknessNight::CppUnitTestFramework;

namespace darknessNight {
	namespace TestsRunner {
		namespace UnitTest {

			class FakeLogger :public MessageLogger {
				std::vector<std::string> messages;
			public:
				virtual void sendMessage(std::string message) override {
					messages.push_back("M:" + message);
				}
				virtual void sendError(std::string message) override {
					messages.push_back("E:" + message);
				}
				virtual void sendWarning(std::string message) override {
					messages.push_back("W:" + message);
				}
				std::vector<std::string> getMessages() {
					return messages;
				}
			};

			class FakeEntry :public Entry {
			public:
				FakeEntry() {
				}

				FakeEntry(std::string p) {
					setPath(p);
				}

				void setPath(std::string p) {
					path = p;
				}
			};

			class FakeDir :public Directory {
				// Inherited via IDirectory
			public:
				std::vector<Entry> retEntries = { FakeEntry("Dll.dll"), FakeEntry("Second.so") };
				virtual std::shared_ptr<Directory> get(std::string path) override {
					auto ptr = std::make_shared<FakeDir>();
					ptr->retEntries = retEntries;
					ptr->path = path;
					return ptr;
				}
				virtual std::vector<Entry> getElements() override {
					return std::vector<Entry>();
				}
				virtual std::vector<Entry> getElementsRecursive() override {
					return std::vector<Entry>();
				}
				virtual std::vector<Entry> searchElements(std::string pattern) override {
					if ((int)pattern.find("\\.(dll|so)") >= 0)
						return retEntries;
					else return std::vector<Entry>();
				}
			};

			class FakeDynamicLibrary : public DynamicLibrary {
			public:
				bool usedDll = false;
				bool usedSo = false;
				bool throwLibraryException = false;
				bool throwFuncException = false;
				bool incorrectLibVer = false;
				TestContainer*(*dllFunc)() = &FakeDynamicLibrary::getTestSuites;
			protected:
				virtual void* getFunction(std::string &module, std::string &func) override {
					throwIfSetted();
					checkHasCorrectLibrary(module);
					return returnFuncIfNameIsCorrect(func);
				}
				void throwIfSetted() {
					if (throwLibraryException)
						throw LibraryLoadException("");
					if (throwFuncException)
						throw FunctionLoadException("");
				}

				void * returnFuncIfNameIsCorrect(std::string & func) {
					if (func == "getTestsFromDynamicTestsLibrary")
						return dllFunc;
					else if (func == "getTestLibVersion")
						return returnLibVerFunc();
					else
						throw FunctionLoadException("");
				}
				void * returnLibVerFunc() {
					if (incorrectLibVer)
						return (const char*(*)())([]()->const char* {return ""; });
					return (const char*(*)())([]()->const char* {return CPPUNITTEST_LIBRARY_VERSION; });
				}
				void checkHasCorrectLibrary(std::string & module) {
					if (module == "Dll.dll")
						usedDll = true;
					else
						if (module == "Second.so")
							usedSo = true;
						else
							throw LibraryLoadException("");
				}

				static TestContainer* getTestSuites() {
					return new TestContainer();
				}
			};

		}
	}
}