#include "SharedLibrary.h"

using namespace darknessNight::SharedLibrary;

#ifdef _WIN32
#include <Windows.h>

DynamicLibrary::~DynamicLibrary() {
	freeAllLibraries();
}

void DynamicLibrary::freeLibrary(std::string name) {
	auto module = modules.find(name);
	if (module != modules.end()) {
		::FreeLibrary((HMODULE)module->second);
		module = modules.erase(module);
	}
}

void DynamicLibrary::freeAllLibraries() {
	for (auto module : modules) {
		::FreeLibrary((HMODULE)module.second);
	}
	modules.clear();
}

void* DynamicLibrary::getFunctionSystemFunc(void* module, std::string&functionName) {
	return (void*)GetProcAddress((HMODULE)module, functionName.c_str());
}

void* DynamicLibrary::loadModuleSystemFunc(std::string&libraryPath) {
	return LoadLibraryA(libraryPath.c_str());
}
#endif
#ifdef __linux
#include <dlfcn.h>

using namespace std;

darknessNight::SharedLibrary::DynamicLibrary::~DynamicLibrary() {
}

void darknessNight::SharedLibrary::DynamicLibrary::freeLibrary(std::string name) {
}


void DynamicLibrary::freeAllLibraries() {
}

void* darknessNight::SharedLibrary::DynamicLibrary::getFunctionSystemFunc(void* module, std::string&functionName) {
	return (void*)dlsym(module, functionName.c_str());
}

void* darknessNight::SharedLibrary::DynamicLibrary::loadModuleSystemFunc(std::string&libraryPath) {
	return dlopen(libraryPath.c_str(), RTLD_LAZY);
}
#endif

void * DynamicLibrary::getFunctionFromModule(void * module, std::string & functionName, std::string &libraryPath) {
	auto func = getFunctionSystemFunc(module, functionName);
	throwIfNotLoadedFunction(func, functionName,libraryPath);
	return func;
}

void* DynamicLibrary::loadModule(std::string &libraryPath) {
	auto module = loadModuleSystemFunc(libraryPath);
	throwIfNotLoadedLibrary(module, libraryPath);
	modules[libraryPath] = module;
	return module;
}

bool DynamicLibrary::moduleExists(std::string & libraryPath) {
	return modules.find(libraryPath) != modules.end();
}

void DynamicLibrary::throwIfNotLoadedFunction(void * func, std::string & functionName, std::string &libraryPath) {
	if (func == nullptr)
		throw FunctionLoadException("Not found function: " + functionName+ " in library: "+libraryPath);
}

void DynamicLibrary::throwIfNotLoadedLibrary(void* module, std::string & libraryPath) {
	if (module == nullptr)
		throw LibraryLoadException("Cannot load library: " + libraryPath);
}

void* DynamicLibrary::getModuleAndLoadIfNeeded(std::string &libraryPath) {
	if (!moduleExists(libraryPath))
		return loadModule(libraryPath);
	else
		return modules[libraryPath];
}

void * DynamicLibrary::getFunction(std::string & libraryPath, std::string & functionName) {
	void* module = getModuleAndLoadIfNeeded(libraryPath);
	return getFunctionFromModule(module, functionName, libraryPath);
}