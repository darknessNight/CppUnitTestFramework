cmake_minimum_required(VERSION 2.8)
project (TestsRunner)
file(GLOB SOURCES ./*.cpp)

include_directories("../../")
target_link_libraries (${PROJECT_NAME} CppUnitTestFramework)
#add_library(${PROJECT_NAME} SHARE ${SOURCES})
add_library(${PROJECT_NAME} SHARE ${SOURCES})

# Install library
#install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
#file(GLOB HEADERS include/*.h)
#install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})