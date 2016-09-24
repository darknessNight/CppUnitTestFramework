cmake_minimum_required (VERSION 2.8.11)
project (CppUnitTestAllProjects)

set(CMAKE_CXX_FLAGS "-std=c++1z")

add_subdirectory (CppUnitTest)
add_subdirectory (Runners)
