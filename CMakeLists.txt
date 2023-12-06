cmake_minimum_required(VERSION 3.27)
include_guard()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/b3a9ba2b8e975550799838332803d468797ae2e1.zip
)
FetchContent_MakeAvailable(googletest)
project(mlone VERSION 1.0
    DESCRIPTION "simple cpu based neural network"
    LANGUAGES CXX)
file(GLOB SOURCES "src/*.cpp")
include_directories(include ${CMAKE_SOURCE_DIR}/build/_deps/googletest-src/googletest/include)
add_executable(mlone.exe ${SOURCES})
enable_testing()

add_executable(
  matrixTest
  src/testing/matrixTest.cc
)
target_link_libraries(
  matrixTest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(matrixTest)
