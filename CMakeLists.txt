cmake_minimum_required (VERSION 3.10)
project(bitter)

file(GLOB bitter_headers ./src/bitter/*.hpp)

add_library(bitter INTERFACE)
add_library(steinwurf::bitter ALIAS bitter)

target_include_directories(bitter INTERFACE src/)

install(FILES ${bitter_headers} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/bitter)
