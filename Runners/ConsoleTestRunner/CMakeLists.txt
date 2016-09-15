cmake_minimum_required(VERSION 2.8)
project (ConsoleTestRunner)
file(GLOB SOURCES ./*.cpp)

include_directories("../ ../../CppUnitTest")
target_link_libraries (${PROJECT_NAME} CppUnitTestFramework TestsRunner)
add_executable(${PROJECT_NAME} ${SOURCES})