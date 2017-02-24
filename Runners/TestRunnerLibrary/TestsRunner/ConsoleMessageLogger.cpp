#include "ConsoleMessageLogger.h"
#include <iostream>

void darknessNight::TestsRunner::ConsoleMessageLogger::sendMessage(std::string message) {
	std::clog << "Info: " << message << "\n";
}

void darknessNight::TestsRunner::ConsoleMessageLogger::sendError(std::string message) {
	std::cerr << "Error: " << message<<std::endl;
}

void darknessNight::TestsRunner::ConsoleMessageLogger::sendWarning(std::string message) {
	std::clog << "Warning: " << message << "\n";
}
