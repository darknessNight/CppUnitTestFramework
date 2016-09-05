cmake_minimum_required(VERSION 2.8)
project (DependencyContainer)
file(GLOB SOURCES ./*.cpp)

add_library(${PROJECT_NAME} ${SOURCES})