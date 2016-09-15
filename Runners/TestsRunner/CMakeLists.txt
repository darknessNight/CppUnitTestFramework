cmake_minimum_required(VERSION 2.8)
project (TestsRunner)
file(GLOB SOURCES ./*.cpp)
file(GLOB SOURCES_FILESYSTEM ./Filesystem/*.cpp)

include_directories("../../CppUnitTest")
add_library(${PROJECT_NAME} ${SOURCES} ${SOURCES_FILESYSTEM})
target_link_libraries (${PROJECT_NAME} CppUnitTestFramework)