cmake_minimum_required(VERSION 2.6)
project (CppUnitTestFramework.CompileTest)
file(GLOB SOURCES ./*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(" ${PROJECT_SOURCE_DIR}/..")
target_link_libraries (${PROJECT_NAME} CppUnitTestFramework)