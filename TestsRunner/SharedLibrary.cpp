#include "SharedLibrary.h"

using namespace darknessNight_SharedLibrary;
std::shared_ptr<SharedLibrary> SharedLibrary::instance = std::make_shared<SharedLibrary>();

#ifdef _WIN32
darknessNight_SharedLibrary::SharedLibrary::~SharedLibrary()
{
	for (auto module : modules) {
		FreeLibrary((HMODULE)module.second);
	}
}

void* SharedLibrary::getModuleAndLoadIfNeeded(std::string &libraryPath) {
	if (modules.find(libraryPath) == modules.end())
		return loadModule(libraryPath);
	else
		return modules[libraryPath];
}


void* SharedLibrary::loadModule(std::string &libraryPath)
{
	auto module = LoadLibraryA(libraryPath.c_str());
	if (module == nullptr)
		throw LibraryLoadException("Cannot load library: " + libraryPath);
	modules[libraryPath] = module;
	return module;
}

#endif
#ifdef __linux
#error Not supported yet
#endif