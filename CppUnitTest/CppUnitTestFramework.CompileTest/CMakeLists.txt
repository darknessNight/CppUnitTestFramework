cmake_minimum_required(VERSION 2.8)
project (CppUnitTestFramework.CompileTest)
file(GLOB SOURCES ./*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
include_directories("../")
target_link_libraries (${PROJECT_NAME} CppUnitTestFramework)