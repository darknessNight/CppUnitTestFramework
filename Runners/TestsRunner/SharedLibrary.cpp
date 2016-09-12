#include "SharedLibrary.h"

using namespace darknessNight::SharedLibrary;
std::shared_ptr<DynamicLibrary> DynamicLibrary::instance = std::make_shared<DynamicLibrary>();

#ifdef _WIN32
#include <Windows.h>

darknessNight::SharedLibrary::DynamicLibrary::~DynamicLibrary()
{
	for (auto module : modules) {
		FreeLibrary((HMODULE)module.second);
	}
}

void darknessNight::SharedLibrary::DynamicLibrary::freeLibrary(std::string name) {
	if (instance->moduleExists(name))
		FreeLibrary((HMODULE)instance->modules[name]);
}

void* darknessNight::SharedLibrary::DynamicLibrary::getFunctionSystemFunc(void* module, std::string&functionName) {
	return (void*)GetProcAddress((HMODULE)module, functionName.c_str());
}

void* darknessNight::SharedLibrary::DynamicLibrary::loadModuleSystemFunc(std::string&libraryPath) {
	return LoadLibraryA(libraryPath.c_str());
}
#endif
#ifdef __linux
#include <dlfcn.h>

darknessNight::SharedLibrary::DynamicLibrary::~DynamicLibrary() {
}

void darknessNight::SharedLibrary::DynamicLibrary::freeLibrary(std::string name) {
}

void* darknessNight::SharedLibrary::DynamicLibrary::getFunctionSystemFunc(void* module, std::string&functionName) {
	return (void*)dlsym(module, functionName.c_str());
}

void* darknessNight::SharedLibrary::DynamicLibrary::loadModuleSystemFunc(std::string&libraryPath) {
	return dlopen(libraryPath.c_str(), RTLD_LAZY);
}
#endif

void * darknessNight::SharedLibrary::DynamicLibrary::getFunctionFromModule(void * module, std::string & functionName) {
	auto func = getFunctionSystemFunc(module, functionName);
	throwIfNotLoadedFunction(func, functionName);
	return func;
}

void* DynamicLibrary::loadModule(std::string &libraryPath) {
	auto module = loadModuleSystemFunc(libraryPath);
	throwIfNotLoadedLibrary(module, libraryPath);
	modules[libraryPath] = module;
	return module;
}

bool darknessNight::SharedLibrary::DynamicLibrary::moduleExists(std::string & libraryPath) {
	return modules.find(libraryPath) != modules.end();
}

void darknessNight::SharedLibrary::DynamicLibrary::throwIfNotLoadedFunction(void * func, std::string & functionName) {
	if (func == nullptr)
		throw FunctionLoadException("Not found function: " + functionName);
}

void darknessNight::SharedLibrary::DynamicLibrary::throwIfNotLoadedLibrary(void* module, std::string & libraryPath) {
	if (module == nullptr)
		throw LibraryLoadException("Cannot load library: " + libraryPath);
}

void* DynamicLibrary::getModuleAndLoadIfNeeded(std::string &libraryPath) {
	if (!moduleExists(libraryPath))
		return loadModule(libraryPath);
	else
		return modules[libraryPath];
}

void * darknessNight::SharedLibrary::DynamicLibrary::getFunction(std::string & libraryPath, std::string & functionName) {
	void* module = instance->getModuleAndLoadIfNeeded(libraryPath);
	return getFunctionFromModule(module, functionName);
}