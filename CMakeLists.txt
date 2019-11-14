cmake_minimum_required (VERSION 3.10)
project(bitter)

add_library(bitter INTERFACE)
add_library(steinwurf::bitter ALIAS bitter)

target_include_directories(bitter INTERFACE src/)
