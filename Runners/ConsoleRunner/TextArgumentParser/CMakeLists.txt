cmake_minimum_required(VERSION 2.8)
project (TextArgumentParser)
file(GLOB SOURCES ./*.cpp)

include_directories("../" "../../CppUnitTest")
add_library(${PROJECT_NAME} ${SOURCES})