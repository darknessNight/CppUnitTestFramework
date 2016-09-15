#include "TestsDiscover.h"
#include "ManagedLibraryChecker.h"
#include <iostream>

darknessNight::TestsRunner::TestsDiscover::TestsDiscover(std::shared_ptr<Directory> dir, std::shared_ptr<DynamicLibrary> dynLibs) {
	dynamicLibrary = dynLibs;
	directory = dir;
}

darknessNight::TestsRunner::TestsDiscover::~TestsDiscover() {
	suites.clear();
}

void darknessNight::TestsRunner::TestsDiscover::findAll(std::vector<std::string> paths, std::vector<std::string> extensions) {
	std::string pattern = prepareSearchPattern(extensions);
	searchLibraries(paths, pattern);
}

void darknessNight::TestsRunner::TestsDiscover::searchLibraries(std::vector<std::string>& paths, std::string & pattern) {
	for (auto path : paths) {
		auto dir = directory->get(path);
		auto tmp = dir->getPath();
		searchLibrariesInDir(dir, pattern);
	}
}

void darknessNight::TestsRunner::TestsDiscover::searchLibrariesInDir(std::shared_ptr<Directory>& directory, std::string & pattern) {
	for (auto dir : directory->searchElements(pattern)) {
		std::cout << "\n;Lib: " << dir.getPath();
		getTestsIfLibraryIsCorrect(dir.getPath());
	}
}

void darknessNight::TestsRunner::TestsDiscover::getTestsIfLibraryIsCorrect(std::string path) {
	try {
		if(isCorrectLibrary(path))
			tryGetTests(path);
	}
	catch (LibraryLoadException) {
	}
	catch (FunctionLoadException) {
		dynamicLibrary->freeLibrary(path);
	}
}

bool darknessNight::TestsRunner::TestsDiscover::isCorrectLibrary(std::string path) {
	return !ManagedLibraryChecker::isManagedLib(path) && isCorrectLibVersion(path);
}

bool darknessNight::TestsRunner::TestsDiscover::isCorrectLibVersion(std::string path) {
	auto func = dynamicLibrary->importFunction<const char*()>(path, dllVersionFuncName);
	std::string dllLibVersion = func();
	std::string programLibVersion = CPPUNITTEST_LIBRARY_VERSION;
	return dllLibVersion == programLibVersion;
}

void darknessNight::TestsRunner::TestsDiscover::tryGetTests(std::string & path) {
	auto func = dynamicLibrary->importFunction<TestContainer*()>(path, dllFuncName);
	TestContainer* container = func();
	for (auto suite : container->getAllTestSuites())
		suites.push_back(suite);		
}

std::string darknessNight::TestsRunner::TestsDiscover::prepareSearchPattern(std::vector<std::string>& extensions) {
	std::string pattern = ".*\\.(";
	addExtensionsToPattern(extensions, pattern);
	return pattern + ")";
}

void darknessNight::TestsRunner::TestsDiscover::addExtensionsToPattern(std::vector<std::string>& extensions, std::string & pattern) {
	for (auto ext : extensions) {
		deleteDotsAtBeginExt(ext);
		pattern += ext + "|";
	}
	pattern = pattern.substr(0, pattern.size() - 1);
}

void darknessNight::TestsRunner::TestsDiscover::deleteDotsAtBeginExt(std::string &ext) {
	while (ext.size() > 0 && ext[0] == '.')
		ext = ext.substr(1);
}

void darknessNight::TestsRunner::TestsDiscover::findInFile(std::string path) {
	getTestsIfLibraryIsCorrect(path);
}

std::vector<std::string> darknessNight::TestsRunner::TestsDiscover::getSuitesNames() {
	std::vector<std::string> names;
	for (auto suite : suites) {
		names.push_back(suite->getName());
	}
	return names;
}

std::vector<TestSuitePtr> darknessNight::TestsRunner::TestsDiscover::getSuites() {
	return suites;
}

std::vector<TestCasePtr> darknessNight::TestsRunner::TestsDiscover::getTestsList() {
	std::vector<TestCasePtr> tests;
	for (auto suite : suites) {
		for (auto test : suite->getTestCases())
			tests.push_back(test);
	}
	return tests;
}

void darknessNight::TestsRunner::TestsDiscover::safeClear() {
	suites.clear();
	dynamicLibrary->freeAllLibraries();
}
