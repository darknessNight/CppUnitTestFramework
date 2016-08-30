cmake_minimum_required(VERSION 2.6)
project (CppUnitTestFrameworkExamples)
file(GLOB SOURCES ./*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
include_directories(" ${PROJECT_SOURCE_DIR}")
target_link_libraries (${PROJECT_NAME} CppUnitTestFramework)