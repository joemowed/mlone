cmake_minimum_required(VERSION 3.27)
include_guard()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ENABLE_FAST_MATH ON)
set(CMAKE_CXX_FLAGS "-O3")
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
file(GLOB TESTSRC "src/*.cpp")
list(FILTER TESTSRC EXCLUDE REGEX "src/main.cpp")
include_directories(${CMAKE_SOURCE_DIR}/build/_deps/googletest-src/googletest/include)
include_directories(src/include)
add_executable(mlone.exe ${SOURCES})
enable_testing()
file(GLOB TESTS "src/testing/*.cc")
add_executable(
  tests.exe
  ${TESTS}
  ${TESTSRC})
target_link_libraries(
  tests.exe
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests.exe)
