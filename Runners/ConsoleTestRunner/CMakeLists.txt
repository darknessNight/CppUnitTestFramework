cmake_minimum_required(VERSION 2.6)
project (ConsoleTestRunner)
file(GLOB SOURCES ./*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})