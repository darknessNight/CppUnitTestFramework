cmake_minimum_required(VERSION 2.6)
project (CppUnitTestFramework)
file(GLOB SOURCES ./*.cpp)

add_library(${PROJECT_NAME} ${SOURCES})