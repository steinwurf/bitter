cmake_minimum_required(VERSION 3.10)
project(bitter)

# Define library
add_library(bitter INTERFACE)
target_compile_features(bitter INTERFACE cxx_std_14)
target_include_directories(bitter INTERFACE src/)
add_library(steinwurf::bitter ALIAS bitter)

# Install headers
install(
  DIRECTORY ./src/bitter
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  FILES_MATCHING
  PATTERN *.hpp)

# Is top level project?
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
  # Build executables
  add_executable(simple_writer examples/simple_writer/simple_writer.cpp)
  target_link_libraries(simple_writer bitter)
  add_executable(simple_reader examples/simple_reader/simple_reader.cpp)
  target_link_libraries(simple_reader bitter)
endif()
